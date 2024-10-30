/* Copyright (c) 2017-2024, Hans Erik Thrane */

#pragma once

#include "roq/args/parser.hpp"

#include "roq/client/flags/settings.hpp"

#include "roq/algo/playground/flags/flags.hpp"
#include "roq/algo/playground/flags/simulation.hpp"

namespace roq {
namespace algo {
namespace playground {

struct Settings final : public client::flags::Settings, public flags::Flags {
  explicit Settings(args::Parser const &);

  flags::Simulation const simulation;
};

}  // namespace playground
}  // namespace algo
}  // namespace roq
