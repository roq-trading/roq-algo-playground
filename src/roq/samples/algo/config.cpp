/* Copyright (c) 2017-2025, Hans Erik Thrane */

#include "roq/samples/algo/config.hpp"

#include "roq/logging.hpp"

using namespace std::literals;

namespace roq {
namespace samples {
namespace algo {

// === IMPLEMENTATION ===

Config::Config(Settings const &settings)
    : strategy_{roq::algo::strategy::Config::parse_file(settings.config_file)},
      simulator_{roq::algo::simulator::Config::parse_file(settings.simulator_config_file)} {
  log::info("config={}"sv, *this);
}

}  // namespace algo
}  // namespace samples
}  // namespace roq
