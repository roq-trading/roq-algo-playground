/* Copyright (c) 2017-2024, Hans Erik Thrane */

#include "roq/samples/algo/factory.hpp"

#include "roq/logging.hpp"

#include "roq/utils/enum.hpp"

#include "roq/algo/strategy/factory.hpp"

#include "roq/algo/matcher/factory.hpp"

#include "roq/algo/reporter/summary.hpp"

using namespace std::literals;

namespace roq {
namespace samples {
namespace algo {

// === IMPLEMENTATION ===

Factory::Factory(Settings const &settings, Config const &config)
    : settings_{settings}, config_{config}, strategy_type_{utils::parse_enum<roq::algo::strategy::Type>(settings_.strategy_type)},
      matcher_type_{utils::parse_enum<decltype(matcher_type_)>(settings.simulation.matcher_type)},
      market_data_source_{utils::parse_enum<decltype(market_data_source_)>(settings.simulation.market_data_source)} {
}

std::unique_ptr<roq::algo::Strategy> Factory::create_strategy(
    roq::algo::Strategy::Dispatcher &dispatcher, roq::algo::OrderCache &order_cache, roq::algo::strategy::Config const &config) const {
  return roq::algo::strategy::Factory::create(strategy_type_, dispatcher, order_cache, config, settings_.strategy_parameters);
}

std::unique_ptr<roq::algo::Reporter> Factory::create_reporter() const {
  auto config = roq::algo::reporter::Summary::Config{
      .market_data_source = market_data_source_,
      .sample_frequency = settings_.simulation.reporter_sample_freq,
  };
  return roq::algo::reporter::Summary::create(config);
}

std::unique_ptr<roq::algo::Matcher> Factory::create_matcher(
    roq::algo::Matcher::Dispatcher &dispatcher, roq::algo::OrderCache &order_cache, roq::algo::matcher::Config const &config) const {
  return roq::algo::matcher::Factory::create(matcher_type_, dispatcher, order_cache, config);
}

}  // namespace algo
}  // namespace samples
}  // namespace roq
