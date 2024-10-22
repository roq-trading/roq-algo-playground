/* Copyright (c) 2017-2024, Hans Erik Thrane */

#include "roq/algo/playground/application.hpp"

#include <magic_enum.hpp>

#include <nameof.hpp>

#include <cassert>
#include <vector>

#include "roq/client.hpp"

#include "roq/algo/matcher/factory.hpp"

#include "roq/algo/reporter/summary.hpp"

#include "roq/algo/playground/strategy.hpp"

using namespace std::literals;
using namespace std::chrono_literals;

namespace roq {
namespace algo {
namespace playground {

// === HELPERS ===

namespace {
template <typename T>
auto parse_enum(auto &value) {
  auto result = magic_enum::enum_cast<T>(value, magic_enum::case_insensitive);
  if (!result.has_value())
    log::fatal(R"(Unexpected: value="{}" ({}))"sv, value, nameof::nameof_full_type<T>());
  return result.value();
}

// note! here we need a callback due to std::string/std::string_view and std::vector/std::span life-time issues
template <typename Callback>
void create_sources(auto &settings, auto &config, auto &params, Callback callback) {
  std::vector<client::Simulator2::Source> result;
  auto size = std::size(params);
  std::vector<client::Simulator2::SymbolsAndPositions> symbols_and_positions(size);
  std::vector<std::vector<client::Simulator2::Account>> accounts(size);
  std::vector<client::Simulator2::Symbols> symbols(size);
  for (size_t i = 0; i < size; ++i) {
    auto &symbols_and_positions_2 = symbols_and_positions[i];
    auto &accounts_2 = accounts[i];
    auto &symbols_2 = symbols[i];
    for (auto &item : config.legs)
      if (i == item.source) {
        assert(!std::empty(item.exchange) && !std::empty(item.symbol));
        symbols_and_positions_2[item.exchange][item.symbol] = 0.0;
        if (!std::empty(item.account) && std::ranges::find_if(accounts_2, [&](auto &item_2) { return item_2.name == item.account; }) == std::end(accounts_2)) {
          auto account = client::Simulator2::Account{
              .name = item.account,
              .symbols_and_positions = symbols_and_positions_2,
          };
          accounts_2.emplace_back(std::move(account));
        }
        symbols_2[item.exchange].emplace(item.symbol);
      }
    auto source = client::Simulator2::Source{
        .path = params[i],
        .name = {},
        .order_management{
            .accounts = accounts_2,
            .latency = settings.simulation.order_management_latency,
        },
        .market_data{
            .symbols = symbols_2,
            .latency = settings.simulation.market_data_latency,
        },
    };
    result.emplace_back(std::move(source));
  }
  callback(result);
}
}  // namespace

// === IMPLEMENTATION ===

int Application::main(roq::args::Parser const &args) {
  auto params = args.params();

  Settings settings{args};
  Config config{settings};

  if (std::size(params) < std::size(config.legs)) {
    roq::log::error("You must provide at least {} argument(s)! (got {})"sv, std::size(config.legs), std::size(params));
    roq::log::error("  For live trading: paths to unix sockets (the .sock files created by the gateways)"sv);
    roq::log::error("  For simulation: paths to event-logs (the .roq files created by the gateways)"sv);
    roq::log::fatal("Unexpected"sv);
  }

  if (settings.simulate) {
    simulation(settings, config, params);
  } else {
    trading(settings, config, params);
  }

  return EXIT_SUCCESS;
}

void Application::trading(Settings const &settings, Config const &config, std::span<std::string_view const> const &params) {
  roq::client::Trader{settings, config, params}.dispatch<Strategy>(settings, config);
}

void Application::simulation(Settings const &settings, Config const &config, std::span<std::string_view const> const &params) {
  auto matcher_type = parse_enum<algo::matcher::Factory::Type>(settings.simulation.matcher_type);
  auto market_data_source = parse_enum<algo::MarketDataSource>(settings.simulation.market_data_source);
  auto reporter_output_type = parse_enum<algo::reporter::OutputType>(settings.simulation.reporter_output_type);

  struct Factory final : public client::Simulator2::Factory {
    Factory(algo::matcher::Factory::Type matcher_type, algo::MarketDataSource market_data_source)
        : matcher_type_{matcher_type}, market_data_source_{market_data_source} {}

    std::unique_ptr<algo::matcher::Handler> create_matcher(
        algo::matcher::Dispatcher &dispatcher,
        algo::OrderCache &order_cache,
        [[maybe_unused]] uint8_t source,
        std::string_view const &exchange,
        std::string_view const &symbol) const override {
      auto config = algo::matcher::Config{
          .exchange = exchange,
          .symbol = symbol,
          .market_data_source = market_data_source_,
      };
      return algo::matcher::Factory::create(matcher_type_, dispatcher, config, order_cache);
    }

   private:
    algo::matcher::Factory::Type const matcher_type_;
    algo::MarketDataSource const market_data_source_;
  } factory{matcher_type, market_data_source};

  auto reporter = [&]() {
    auto config = algo::reporter::Summary::Config{
        .market_data_source = market_data_source,
        .sample_frequency = settings.simulation.reporter_sample_freq,
    };
    return algo::reporter::Summary::create(config);
  }();

  auto dispatch_helper = [&](auto &sources) {  // note! callback due to life-time issues
    roq::client::Simulator2{settings, config, factory, *reporter, sources}.dispatch<Strategy>(settings, config);
  };
  create_sources(settings, config, params, dispatch_helper);

  (*reporter).print(reporter_output_type);
}

}  // namespace playground
}  // namespace algo
}  // namespace roq
