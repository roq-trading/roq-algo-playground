/* Copyright (c) 2017-2024, Hans Erik Thrane */

#include "roq/arbitrage/settings.hpp"

namespace roq {
namespace arbitrage {

Settings::Settings(roq::args::Parser const &args)
    : roq::client::flags::Settings{args}, flags::Flags{flags::Flags::create()}, model{flags::Model::create()}, simulation{flags::Simulation::create()} {
}

}  // namespace arbitrage
}  // namespace roq
