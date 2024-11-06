/* Copyright (c) 2017-2024, Hans Erik Thrane */

#pragma once

#include <fmt/core.h>
#include <fmt/ranges.h>

#include <string>
#include <vector>

#include "roq/algo/leg.hpp"

#include "roq/algo/strategy/config.hpp"
#include "roq/algo/strategy/type.hpp"

#include "roq/samples/algo/settings.hpp"

namespace roq {
namespace samples {
namespace algo {

struct Config final {
  explicit Config(Settings const &);

  Config(Config &&) = default;
  Config(Config const &) = delete;

  operator roq::algo::strategy::Config() const {
    return {
        .legs = strategy.legs,
        .strategy_id = {},
    };
  }

  struct {
    roq::algo::strategy::Type const type;
    std::vector<roq::algo::Leg> const legs;
  } strategy;
};

}  // namespace algo
}  // namespace samples
}  // namespace roq

template <>
struct fmt::formatter<roq::samples::algo::Config> {
  constexpr auto parse(format_parse_context &context) { return std::begin(context); }
  auto format(roq::samples::algo::Config const &value, format_context &context) const {
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
