/* Copyright (c) 2017-2025, Hans Erik Thrane */

#pragma once

#include <fmt/core.h>

#include "roq/algo/strategy/config.hpp"

#include "roq/algo/simulator/config.hpp"

#include "roq/samples/algo/settings.hpp"

namespace roq {
namespace samples {
namespace algo {

struct Config final {
  explicit Config(Settings const &);

  Config(Config &&) = default;
  Config(Config const &) = delete;

  operator roq::algo::strategy::Config const &() const { return strategy_; }
  operator roq::algo::simulator::Config const &() const { return simulator_; }

 protected:
  roq::algo::strategy::Config const strategy_;
  roq::algo::simulator::Config const simulator_;
};

}  // namespace algo
}  // namespace samples
}  // namespace roq

template <>
struct fmt::formatter<roq::samples::algo::Config> {
  constexpr auto parse(format_parse_context &context) { return std::begin(context); }
  auto format(roq::samples::algo::Config const &value, format_context &context) const {
    using namespace std::literals;
    auto &strategy = static_cast<roq::algo::strategy::Config const &>(value);
    auto &simulator = static_cast<roq::algo::simulator::Config const &>(value);
    return fmt::format_to(
        context.out(),
        R"({{)"
        R"(strategy={}, )"
        R"(simulator={})"
        R"(}})"sv,
        strategy,
        simulator);
  }
};
