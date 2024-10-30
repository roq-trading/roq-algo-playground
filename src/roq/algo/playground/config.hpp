/* Copyright (c) 2017-2024, Hans Erik Thrane */

#pragma once

#include <fmt/core.h>
#include <fmt/ranges.h>

#include <string>
#include <vector>

#include "roq/algo/leg.hpp"

#include "roq/algo/strategy/config.hpp"
#include "roq/algo/strategy/type.hpp"

#include "roq/algo/playground/settings.hpp"

namespace roq {
namespace algo {
namespace playground {

struct Config final {
  explicit Config(Settings const &);

  Config(Config &&) = default;
  Config(Config const &) = delete;

  operator algo::strategy::Config() const {
    return {
        .legs = strategy.legs,
        .strategy_id = {},
    };
  }

  struct {
    algo::strategy::Type const type;
    std::vector<algo::Leg> const legs;
  } strategy;
};

}  // namespace playground
}  // namespace algo
}  // namespace roq

template <>
struct fmt::formatter<roq::algo::playground::Config> {
  constexpr auto parse(format_parse_context &context) { return std::begin(context); }
  auto format(roq::algo::playground::Config const &value, format_context &context) const {
    using namespace std::literals;
    return fmt::format_to(
        context.out(),
        R"({{)"
        R"(strategy={{)"
        R"(type={}, )"
        R"(legs=[{}])"
        R"(}})"
        R"(}})"sv,
        value.strategy.type,
        fmt::join(value.strategy.legs, ", "sv));
  }
};
