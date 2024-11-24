/* Copyright (c) 2017-2025, Hans Erik Thrane */

#include "roq/samples/algo/strategy/factory.hpp"

#include "roq/logging.hpp"

#include "roq/utils/variant/parse.hpp"

#include "roq/utils/key_value/parser.hpp"

#include "roq/samples/algo/strategy/arbitrage.hpp"

using namespace std::literals;

namespace roq {
namespace samples {
namespace algo {
namespace strategy {

// === HELPERS ===

namespace {
auto parameters_from_string(auto &parameters) {
  Parameters result;
  // parse
  auto callback = [&](auto &key, auto &value) {
    assert(!std::empty(key));
    assert(!std::empty(value));
    enum class Key {
      MARKET_DATA_SOURCE,
      MAX_AGE,
      THRESHOLD,
      QUANTITY_0,
      MIN_POSITION_0,
      MAX_POSITION_0,
      PUBLISH_SOURCE,
    };
    auto key_2 = utils::parse_enum<Key>(key);
    log::debug(R"(key={}, value="{}")"sv, magic_enum::enum_name(key_2), value);
    switch (key_2) {
      case Key::MARKET_DATA_SOURCE:
        utils::variant::parse(result.market_data_source, value);
        break;
      case Key::MAX_AGE:
        result.max_age = 10s;  // XXX FIXME TODO parse period
        break;
      case Key::THRESHOLD:
        utils::variant::parse(result.threshold, value);
        break;
      case Key::QUANTITY_0:
        utils::variant::parse(result.quantity_0, value);
        break;
      case Key::MIN_POSITION_0:
        utils::variant::parse(result.min_position_0, value);
        break;
      case Key::MAX_POSITION_0:
        utils::variant::parse(result.max_position_0, value);
        break;
      case Key::PUBLISH_SOURCE:
        utils::variant::parse(result.publish_source, value);
        break;
    }
  };
  utils::key_value::Parser::dispatch(parameters, callback);
  // validate
  // XXX FIXME TODO implement
  return result;
}
}  // namespace

// === IMPLEMENTATION ===

std::unique_ptr<roq::algo::Strategy> Factory::create(
    roq::algo::Strategy::Dispatcher &dispatcher, roq::algo::OrderCache &order_cache, roq::algo::strategy::Config const &config, Parameters const &parameters) {
  return std::make_unique<Arbitrage>(dispatcher, order_cache, config, parameters);
}

std::unique_ptr<roq::algo::Strategy> Factory::create(
    roq::algo::Strategy::Dispatcher &dispatcher,
    roq::algo::OrderCache &order_cache,
    roq::algo::strategy::Config const &config,
    std::string_view const &parameters) {
  auto parameters_2 = parameters_from_string(parameters);
  return create(dispatcher, order_cache, config, parameters_2);
}

}  // namespace strategy
}  // namespace algo
}  // namespace samples
}  // namespace roq
