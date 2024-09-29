/* Copyright (c) 2017-2024, Hans Erik Thrane */

#pragma once

#include "roq/args/parser.hpp"

#include "roq/client/flags/settings.hpp"

#include "roq/arbitrage/flags/flags.hpp"
#include "roq/arbitrage/flags/model.hpp"
#include "roq/arbitrage/flags/simulation.hpp"

namespace roq {
namespace arbitrage {

struct Settings final : public roq::client::flags::Settings, public flags::Flags {
  explicit Settings(roq::args::Parser const &);

  flags::Model const model;
  flags::Simulation const simulation;
};

}  // namespace arbitrage
}  // namespace roq
