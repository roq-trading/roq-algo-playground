/* Copyright (c) 2017-2024, Hans Erik Thrane */

#include "roq/arbitrage/application.hpp"

#include <magic_enum.hpp>

#include <cassert>
#include <vector>

#include "roq/client.hpp"

#include "roq/algo/matcher/factory.hpp"

#include "roq/algo/reporter/summary.hpp"

#include "roq/arbitrage/settings.hpp"

using namespace std::literals;
using namespace std::chrono_literals;  // NOLINT

namespace roq {
namespace arbitrage {

// === HELPERS ===

namespace {
auto create_symbols(auto &settings) {
  assert(std::size(settings.exchanges) == std::size(settings.symbols));
  using result_type = client::Simulator2::Symbols;
  result_type result;
  for (size_t i = 0; i < std::size(settings.exchanges); ++i) {
    auto &exchange = settings.exchanges[i];
    auto &symbol = settings.symbols[i];
    result[std::string{exchange}].emplace(symbol);
  }
  return result;
}

auto create_symbols_and_positions(auto &settings) {
  assert(std::size(settings.exchanges) == std::size(settings.symbols));
  using result_type = client::Simulator2::SymbolsAndPositions;
  result_type result;
  for (size_t i = 0; i < std::size(settings.exchanges); ++i) {
    auto &exchange = settings.exchanges[i];
    auto &symbol = settings.symbols[i];
    result[std::string{exchange}].emplace(symbol, 0.0);  // note! initial position
  }
  return result;
}

auto create_accounts(auto &settings, auto &symbols_and_positions) {
  using result_type = std::vector<client::Simulator2::Account>;
  result_type result;
  for (auto &account : settings.accounts)
    result.emplace_back(account, symbols_and_positions);
  return result;
}

auto create_sources(auto &settings, auto &params, auto &accounts, auto &symbols) {
  using result_type = std::vector<client::Simulator2::Source>;
  result_type result;
  for (auto &item : params) {
    auto source = client::Simulator2::Source{
        .path = item,
        .name = {},
        .order_management{
            .accounts = accounts,
            .latency = settings.simulation.order_management_latency,
        },
        .market_data{
            .symbols = symbols,
            .latency = settings.simulation.market_data_latency,
        },
    };
    result.emplace_back(std::move(source));
  }
  return result;
}
}  // namespace

// === IMPLEMENTATION ===

int Application::main(roq::args::Parser const &args) {
  auto params = args.params();
  if (std::empty(params)) {
    roq::log::warn("You must provide at least one argument!"sv);
    roq::log::warn("  For simulation: paths to event-logs (the .roq files created by gateways)"sv);
    roq::log::warn("  For live trading: paths to unix sockets (the .sock files created by gateways)"sv);
    roq::log::fatal("Unexpected"sv);
  }
  Settings settings{args};
  Config config{settings};
  if (settings.simulate) {
    simulation(settings, config, params);
  } else {
    trading(settings, config, params);
  }
  return EXIT_SUCCESS;
}

void Application::simulation(Settings const &settings, Config const &config, std::span<std::string_view const> const &params) {
  auto symbols = create_symbols(settings);
  auto symbols_and_positions = create_symbols_and_positions(settings);
  auto accounts = create_accounts(settings, symbols_and_positions);
  auto sources = create_sources(settings, params, accounts, symbols);

  struct Factory final : public client::Simulator2::Factory {
    explicit Factory(Settings const &settings)
        : type_{magic_enum::enum_cast<decltype(type_)>(settings.simulation.matcher_type, magic_enum::case_insensitive).value()},
          market_data_source_{
              magic_enum::enum_cast<decltype(market_data_source_)>(settings.simulation.market_data_source, magic_enum::case_insensitive).value()} {}

    std::unique_ptr<algo::matcher::Handler> create_matcher(
        algo::matcher::Dispatcher &dispatcher,
        algo::Cache &cache,
        uint8_t source_id,
        std::string_view const &exchange,
        std::string_view const &symbol) const override {
      auto config = algo::matcher::Config{
          .instrument{
              .source = source_id,
              .exchange = exchange,
              .symbol = symbol,
              .account = {},
          },
          .market_data_source = market_data_source_,
      };
      return algo::matcher::Factory::create(type_, dispatcher, config, cache);
    }

   private:
    algo::matcher::Factory::Type const type_;
    algo::MarketDataSource const market_data_source_;
  } factory{settings};

  auto reporter = [&]() {
    auto config = algo::reporter::Summary::Config{
        .frequency = 1min,
    };
    return algo::reporter::Summary::create(config);
  }();

  roq::client::Simulator2{settings, config, factory, *reporter, sources}.dispatch<value_type>(settings);

  (*reporter).print();
}

void Application::trading(Settings const &settings, Config const &config, std::span<std::string_view const> const &params) {
  roq::client::Trader{settings, config, params}.dispatch<value_type>(settings);
}

}  // namespace arbitrage
}  // namespace roq
