/* Copyright (c) 2017-2025, Hans Erik Thrane */

#pragma once

#include "roq/args/parser.hpp"

#include "roq/client/flags/settings.hpp"

#include "roq/samples/algo/flags/flags.hpp"
#include "roq/samples/algo/flags/simulation.hpp"

namespace roq {
namespace samples {
namespace algo {

struct Settings final : public client::flags::Settings, public flags::Flags {
  explicit Settings(args::Parser const &);

  flags::Simulation const simulation;
};

}  // namespace algo
}  // namespace samples
}  // namespace roq
