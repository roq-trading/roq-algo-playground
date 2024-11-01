/* Copyright (c) 2017-2024, Hans Erik Thrane */

#pragma once

#include "roq/client.hpp"

#include "roq/algo/market_data_source.hpp"

#include "roq/algo/matcher/type.hpp"

#include "roq/algo/playground/config.hpp"
#include "roq/algo/playground/settings.hpp"

namespace roq {
namespace algo {
namespace playground {

struct Factory final : public client::Simulator2::Factory {
  Factory(Settings const &, Config const &);

  std::unique_ptr<algo::Strategy> create_strategy(algo::Strategy::Dispatcher &, algo::OrderCache &, algo::strategy::Config const &) const override;

  std::unique_ptr<algo::Reporter> create_reporter() const override;

  std::unique_ptr<algo::Matcher> create_matcher(algo::Matcher::Dispatcher &, algo::OrderCache &, algo::matcher::Config const &) const override;

 private:
  Settings const &settings_;
  Config const &config_;
  algo::matcher::Type const matcher_type_;
  algo::MarketDataSource const market_data_source_;
};

}  // namespace playground
}  // namespace algo
}  // namespace roq
