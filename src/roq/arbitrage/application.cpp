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
template <typename T>
auto parse_enum(auto &value) {
  auto result = magic_enum::enum_cast<T>(value, magic_enum::case_insensitive);
  if (!result.has_value())
    log::fatal(R"(Unexpected: value="{}")"sv, value);
  return result.value();
}

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
    roq::log::warn("You must provide {} argument(s)! (Got {})"sv, std::size(config.legs), std::size(params));
    roq::log::warn("  For simulation: paths to event-logs (the .roq files created by gateways)"sv);
    roq::log::warn("  For live trading: paths to unix sockets (the .sock files created by gateways)"sv);
    roq::log::fatal("Unexpected"sv);
  }

  if (settings.simulate) {
    simulation(settings, config, params);
  } else {
    trading(settings, config, params);
  }

  return EXIT_SUCCESS;
}

void Application::simulation(Settings const &settings, Config const &config, std::span<std::string_view const> const &params) {
  struct Factory final : public client::Simulator2::Factory {
    explicit Factory(Settings const &settings)
        : type_{parse_enum<decltype(type_)>(settings.simulation.matcher_type)},
          market_data_source_{parse_enum<decltype(market_data_source_)>(settings.simulation.market_data_source)} {}

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
      return algo::matcher::Factory::create(type_, dispatcher, config, order_cache);
    }

   private:
    algo::matcher::Factory::Type const type_;
    algo::MarketDataSource const market_data_source_;
  } factory{settings};

  auto reporter = [&]() {
    auto config = algo::reporter::Summary::Config{
        .market_data_source = algo::MarketDataSource::TOP_OF_BOOK,
        .sample_frequency = 1min,
    };
    return algo::reporter::Summary::create(config);
  }();

  auto callback = [&](auto &sources) { roq::client::Simulator2{settings, config, factory, *reporter, sources}.dispatch<value_type>(settings, config); };

  create_sources(settings, config, params, callback);

  auto output_type = parse_enum<algo::reporter::OutputType>(settings.simulation.output_type);

  (*reporter).print(output_type);
}

void Application::trading(Settings const &settings, Config const &config, std::span<std::string_view const> const &params) {
  roq::client::Trader{settings, config, params}.dispatch<value_type>(settings, config);
}

}  // namespace arbitrage
}  // namespace roq
