/* Copyright (c) 2017-2024, Hans Erik Thrane */

#include "roq/algo/playground/factory.hpp"

#include <magic_enum.hpp>

#include <nameof.hpp>

#include "roq/logging.hpp"

#include "roq/algo/strategy/factory.hpp"

#include "roq/algo/matcher/factory.hpp"

#include "roq/algo/reporter/summary.hpp"

using namespace std::literals;

namespace roq {
namespace algo {
namespace playground {

// === HELPERS ===

namespace {
template <typename T>
auto parse_enum(auto &value) {
  auto result = magic_enum::enum_cast<T>(value, magic_enum::case_insensitive);
  if (!result.has_value())
    log::fatal(R"(Unexpected: value="{}" ({}))"sv, value, nameof::nameof_full_type<T>());
  return result.value();
}
}  // namespace

// === IMPLEMENTATION ===

Factory::Factory(Settings const &settings, Config const &config)
    : settings_{settings}, config_{config}, matcher_type_{parse_enum<decltype(matcher_type_)>(settings.simulation.matcher_type)},
      market_data_source_{parse_enum<decltype(market_data_source_)>(settings.simulation.market_data_source)} {
}

std::unique_ptr<algo::Strategy> Factory::create_strategy(
    algo::Strategy::Dispatcher &dispatcher, algo::OrderCache &order_cache, algo::strategy::Config const &config) const {
  return algo::strategy::Factory::create(config_.strategy.type, dispatcher, order_cache, config, settings_.parameters);
}

std::unique_ptr<algo::Reporter> Factory::create_reporter() const {
  auto config = algo::reporter::Summary::Config{
      .market_data_source = market_data_source_,
      .sample_frequency = settings_.simulation.reporter_sample_freq,
  };
  return algo::reporter::Summary::create(config);
}

std::unique_ptr<algo::Matcher> Factory::create_matcher(
    algo::Matcher::Dispatcher &dispatcher,
    algo::OrderCache &order_cache,
    uint8_t source,
    std::string_view const &exchange,
    std::string_view const &symbol) const {
  auto config = algo::matcher::Config{
      .source = source,
      .exchange = exchange,
      .symbol = symbol,
      .market_data_source = market_data_source_,
  };
  return algo::matcher::Factory::create(matcher_type_, dispatcher, config, order_cache);
}

}  // namespace playground
}  // namespace algo
}  // namespace roq
