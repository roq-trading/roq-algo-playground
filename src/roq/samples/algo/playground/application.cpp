/* Copyright (c) 2017-2024, Hans Erik Thrane */

#include "roq/samples/algo/playground/application.hpp"

#include <magic_enum.hpp>

#include <nameof.hpp>

#include "roq/client.hpp"

using namespace std::literals;
using namespace std::chrono_literals;

namespace roq {
namespace samples {
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
}  // namespace

// === IMPLEMENTATION ===

int Application::main(args::Parser const &args) {
  auto params = args.params();

  Settings settings{args};
  Config config{settings};

  if (std::size(params) < std::size(config.strategy.legs)) {
    log::error("You must provide at least {} argument(s)! (got {})"sv, std::size(config.strategy.legs), std::size(params));
    log::error("  For live trading: paths to unix sockets (the .sock files created by the gateways)"sv);
    log::error("  For simulation: paths to event-logs (the .roq files created by the gateways)"sv);
    log::fatal("Unexpected"sv);
  }

  Factory factory{settings, config};

  if (settings.simulate) {
    simulation(settings, factory, config, params);
  } else {
    trading(settings, factory, config, params);
  }

  return EXIT_SUCCESS;
}

void Application::simulation(
    Settings const &settings, Factory const &factory, roq::algo::strategy::Config const &config, std::span<std::string_view const> const &params) {
  auto output_type = parse_enum<roq::algo::reporter::OutputType>(settings.simulation.reporter_output_type);
  auto reporter = client::Simulator2::dispatch(settings, factory, config, params);
  (*reporter).print(output_type, settings.simulation.reporter_label);
}

void Application::trading(
    Settings const &settings, Factory const &factory, roq::algo::strategy::Config const &config, std::span<std::string_view const> const &params) {
  client::Trader2::dispatch(settings, factory, config, params);
}

}  // namespace playground
}  // namespace algo
}  // namespace samples
}  // namespace roq
