/* Copyright (c) 2017-2024, Hans Erik Thrane */

#include "roq/algo/playground/settings.hpp"

namespace roq {
namespace algo {
namespace playground {

Settings::Settings(args::Parser const &args) : client::flags::Settings{args}, flags::Flags{flags::Flags::create()}, simulation{flags::Simulation::create()} {
}

}  // namespace playground
}  // namespace algo
}  // namespace roq
