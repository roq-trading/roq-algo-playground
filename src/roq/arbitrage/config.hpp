/* Copyright (c) 2017-2024, Hans Erik Thrane */

#pragma once

#include <fmt/core.h>
#include <fmt/ranges.h>

#include <string>
#include <vector>

#include "roq/margin_mode.hpp"
#include "roq/position_effect.hpp"
#include "roq/time_in_force.hpp"

#include "roq/client/config.hpp"

#include "roq/arbitrage/settings.hpp"

namespace roq {
namespace arbitrage {

struct Config final : public roq::client::Config {
  explicit Config(Settings const &);

  Config(Config &&) = default;
  Config(Config const &) = delete;

 protected:
  void dispatch(Handler &) const override;

 private:
  Settings const &settings_;

 public:
  struct Leg final {
    uint8_t source = {};
    std::string account;
    std::string exchange;
    std::string symbol;
    PositionEffect position_effect = {};
    MarginMode margin_mode = {};
    TimeInForce time_in_force = {};
  };
  std::vector<Leg> legs;
};

}  // namespace arbitrage
}  // namespace roq

template <>
struct fmt::formatter<roq::arbitrage::Config::Leg> {
  constexpr auto parse(format_parse_context &context) { return std::begin(context); }
  auto format(roq::arbitrage::Config::Leg const &value, format_context &context) const {
    using namespace std::literals;
    return fmt::format_to(
        context.out(),
        R"({{)"
        R"(source={}, )"
        R"(account="{}", )"
        R"(exchange="{}", )"
        R"(symbol="{}", )"
        R"(position_effect={}, )"
        R"(margin_mode={}, )"
        R"(time_in_force={})"
        R"(}})"sv,
        value.source,
        value.account,
        value.exchange,
        value.symbol,
        value.position_effect,
        value.margin_mode,
        value.time_in_force);
  }
};

template <>
struct fmt::formatter<roq::arbitrage::Config> {
  constexpr auto parse(format_parse_context &context) { return std::begin(context); }
  auto format(roq::arbitrage::Config const &value, format_context &context) const {
    using namespace std::literals;
    return fmt::format_to(
        context.out(),
        R"({{)"
        R"(legs=[{}])"
        R"(}})"sv,
        fmt::join(value.legs, ", "sv));
  }
};
