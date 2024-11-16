/* Copyright (c) 2017-2024, Hans Erik Thrane */

#include "roq/samples/algo/application.hpp"

#include "roq/utils/enum.hpp"

#include "roq/client.hpp"

using namespace std::literals;

namespace roq {
namespace samples {
namespace algo {

// === IMPLEMENTATION ===

int Application::main(args::Parser const &args) {
  auto params = args.params();

  Settings settings{args};
  Config config{settings};

  auto size = std::size(static_cast<roq::algo::strategy::Config const &>(config).legs);
  if (std::size(params) < size) {
    log::error("You must provide at least {} argument(s)! (got {})"sv, size, std::size(params));
    log::error("  For live trading: paths to unix sockets (the .sock files created by the gateways)"sv);
    log::error("  For simulation: paths to event-logs (the .roq files created by the gateways)"sv);
    log::fatal("Unexpected"sv);
  }

  Factory factory{settings, config};

  if (settings.simulate) {
    simulate(settings, factory, config, params);
  } else {
    trade(settings, factory, config, params);
  }

  return EXIT_SUCCESS;
}

void Application::simulate(Settings const &settings, Factory const &factory, Config const &config, std::span<std::string_view const> const &params) {
  auto output_type = utils::parse_enum<roq::algo::reporter::OutputType>(settings.simulation.reporter_output_type);
  auto reporter = client::Simulator2::dispatch(settings, factory, config, config, params);
  (*reporter).print(output_type, settings.simulation.reporter_label);
}

void Application::trade(Settings const &settings, Factory const &factory, Config const &config, std::span<std::string_view const> const &params) {
  client::Trader2::dispatch(settings, factory, config, params);
}

}  // namespace algo
}  // namespace samples
}  // namespace roq
