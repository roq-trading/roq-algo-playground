/* Copyright (c) 2017-2024, Hans Erik Thrane */

#include "roq/algo/playground/application.hpp"

#include <magic_enum.hpp>

#include <nameof.hpp>

#include <cassert>
#include <vector>

#include "roq/client.hpp"

#include "roq/algo/matcher/factory.hpp"
#include "roq/algo/reporter/summary.hpp"
#include "roq/algo/strategy/factory.hpp"

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
    for (auto &item : config.strategy.legs)
      if (i == item.source) {
        auto account = static_cast<std::string_view>(item.account);
        auto exchange = static_cast<std::string_view>(item.exchange);
        auto symbol = static_cast<std::string_view>(item.symbol);
        assert(!std::empty(exchange) && !std::empty(symbol));
        symbols_and_positions_2[std::string{exchange}][std::string{symbol}] = 0.0;
        if (!std::empty(account) && std::ranges::find_if(accounts_2, [&](auto &item_2) { return item_2.name == account; }) == std::end(accounts_2)) {
          auto account_2 = client::Simulator2::Account{
              .name = account,
              .symbols_and_positions = symbols_and_positions_2,
          };
          accounts_2.emplace_back(std::move(account_2));
        }
        symbols_2[std::string{exchange}].emplace(symbol);
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

  if (std::size(params) < std::size(config.strategy.legs)) {
    roq::log::error("You must provide at least {} argument(s)! (got {})"sv, std::size(config.strategy.legs), std::size(params));
    roq::log::error("  For live trading: paths to unix sockets (the .sock files created by the gateways)"sv);
    roq::log::error("  For simulation: paths to event-logs (the .roq files created by the gateways)"sv);
    roq::log::fatal("Unexpected"sv);
  }

  Factory factory{settings, config};

  if (settings.simulate) {
    auto helper = [&](auto &sources) { simulation(settings, factory, sources); };
    create_sources(settings, config, params, helper);
  } else {
    trading(settings, factory, params);
  }

  return EXIT_SUCCESS;
}

void Application::simulation(Settings const &settings, Factory const &factory, std::span<client::Simulator2::Source const> const &sources) {
  auto output_type = parse_enum<algo::reporter::OutputType>(settings.simulation.reporter_output_type);
  auto reporter = roq::client::Simulator2::dispatch(settings, factory, sources);
  (*reporter).print(output_type, settings.simulation.reporter_label);
}

void Application::trading(Settings const &settings, Factory const &factory, std::span<std::string_view const> const &params) {
  roq::client::Trader2::dispatch(settings, factory, params);
}

}  // namespace playground
}  // namespace algo
}  // namespace roq
