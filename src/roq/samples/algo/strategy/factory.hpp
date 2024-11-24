/* Copyright (c) 2017-2025, Hans Erik Thrane */

#pragma once

#include <memory>
#include <string_view>

#include "roq/algo/order_cache.hpp"
#include "roq/algo/strategy.hpp"
#include "roq/algo/strategy/config.hpp"

#include "roq/samples/algo/strategy/parameters.hpp"

namespace roq {
namespace samples {
namespace algo {
namespace strategy {

struct Factory final {
  static std::unique_ptr<roq::algo::Strategy> create(
      roq::algo::Strategy::Dispatcher &, roq::algo::OrderCache &, roq::algo::strategy::Config const &, Parameters const &);
  static std::unique_ptr<roq::algo::Strategy> create(
      roq::algo::Strategy::Dispatcher &, roq::algo::OrderCache &, roq::algo::strategy::Config const &, std::string_view const &parameters);
};

}  // namespace strategy
}  // namespace algo
}  // namespace samples
}  // namespace roq
