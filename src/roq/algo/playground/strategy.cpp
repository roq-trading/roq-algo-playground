/* Copyright (c) 2017-2024, Hans Erik Thrane */

#include "roq/algo/playground/strategy.hpp"

#include <magic_enum.hpp>

#include <nameof.hpp>

#include "roq/logging.hpp"

#include "roq/utils/safe_cast.hpp"

#include "roq/algo/strategy/factory.hpp"

#include "roq/algo/playground/flags/flags.hpp"

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
    log::fatal(R"(Unexpected: value="{}")"sv, value, nameof::nameof_full_type<T>());
  return result.value();
}

auto create_strategy(auto &dispatcher, auto &settings, auto &order_cache, auto &config) {
  std::vector<algo::strategy::Leg> legs;
  for (auto &item : config.legs) {
    auto leg = algo::strategy::Leg{
        .source = item.source,
        .account = item.account,
        .exchange = item.exchange,
        .symbol = item.symbol,
        .position_effect = item.position_effect,
        .margin_mode = item.margin_mode,
        .time_in_force = item.time_in_force,
    };
    legs.emplace_back(std::move(leg));
  }
  auto config_2 = algo::strategy::Config{
      .legs = legs,
      .strategy_id = {},
  };
  return algo::strategy::Factory::create(config.type, dispatcher, order_cache, config_2, settings.parameters);
}
}  // namespace

// === IMPLEMENTATION ===

Strategy::Strategy(roq::client::Dispatcher &dispatcher, Settings const &settings, Config const &config)
    : dispatcher_{dispatcher}, strategy_{create_strategy(*this, settings, *this, config)} {
}

// client::Handler

// host

void Strategy::operator()(Event<Start> const &event) {
  (*strategy_)(event);
}

void Strategy::operator()(Event<Stop> const &event) {
  (*strategy_)(event);
}

void Strategy::operator()(Event<Timer> const &event) {
  (*strategy_)(event);
}

void Strategy::operator()(Event<Connected> const &event) {
  (*strategy_)(event);
}

void Strategy::operator()(Event<Disconnected> const &event) {
  (*strategy_)(event);
}

// control

void Strategy::operator()(Event<DownloadBegin> const &event) {
  (*strategy_)(event);
}

void Strategy::operator()(Event<DownloadEnd> const &event) {
  (*strategy_)(event);
}

void Strategy::operator()(Event<Ready> const &event) {
  (*strategy_)(event);
}

// config

void Strategy::operator()(Event<GatewaySettings> const &event) {
  (*strategy_)(event);
}

// stream

void Strategy::operator()(Event<StreamStatus> const &event) {
  (*strategy_)(event);
}

void Strategy::operator()(Event<ExternalLatency> const &event) {
  (*strategy_)(event);
}

void Strategy::operator()(Event<RateLimitsUpdate> const &event) {
  (*strategy_)(event);
}

void Strategy::operator()(Event<RateLimitTrigger> const &event) {
  (*strategy_)(event);
}

// service

void Strategy::operator()(Event<GatewayStatus> const &event) {
  (*strategy_)(event);
}

// market data

void Strategy::operator()(Event<ReferenceData> const &event) {
  (*strategy_)(event);
}

void Strategy::operator()(Event<MarketStatus> const &event) {
  (*strategy_)(event);
}

void Strategy::operator()(Event<TopOfBook> const &event) {
  (*strategy_)(event);
}

void Strategy::operator()(Event<MarketByPriceUpdate> const &event) {
  (*strategy_)(event);
}

void Strategy::operator()(Event<MarketByOrderUpdate> const &event) {
  (*strategy_)(event);
}

void Strategy::operator()(Event<TradeSummary> const &event) {
  (*strategy_)(event);
}

void Strategy::operator()(Event<StatisticsUpdate> const &event) {
  (*strategy_)(event);
}

// market data (derived)

void Strategy::operator()(Event<TimeSeriesUpdate> const &event) {
  (*strategy_)(event);
}

// order management

void Strategy::operator()(Event<CancelAllOrdersAck> const &event) {
  (*strategy_)(event);
}

void Strategy::operator()(Event<OrderAck> const &event) {
  auto &[message_info, order_ack] = event;
  auto iter = orders_.find(order_ack.order_id);
  if (iter == std::end(orders_)) [[unlikely]]
    log::fatal("Unexpected: event={}"sv, event);  // note! gateway should only respond to requests from this session => internal error
  (*strategy_)(event, (*iter).second);
}

void Strategy::operator()(Event<OrderUpdate> const &event) {
  auto &[message_info, order_update] = event;
  auto iter = orders_.find(order_update.order_id);
  if (iter == std::end(orders_)) {
    cache::Order order{event};
    auto res = orders_.emplace(order_update.order_id, std::move(order));
    assert(res.second);
    iter = res.first;
  }
  (*strategy_)(event, (*iter).second);
}

void Strategy::operator()(Event<TradeUpdate> const &event) {
  auto &[message_info, trade_update] = event;
  auto iter = orders_.find(trade_update.order_id);
  if (iter == std::end(orders_)) [[unlikely]]
    log::fatal("Unexpected: event={}"sv, event);  // note! a trade must have an associated order => internal error
  (*strategy_)(event, (*iter).second);
}

// account management (exchange)

void Strategy::operator()(Event<PositionUpdate> const &event) {
  (*strategy_)(event);
}

void Strategy::operator()(Event<FundsUpdate> const &event) {
  (*strategy_)(event);
}

// parameters

void Strategy::operator()(Event<ParametersUpdate> const &event) {
  (*strategy_)(event);
}

// position manager (service)

void Strategy::operator()(Event<PortfolioUpdate> const &event) {
  (*strategy_)(event);
}

// risk managemenet

void Strategy::operator()(Event<RiskLimitsUpdate> const &event) {
  (*strategy_)(event);
}

// metrics

void Strategy::operator()(metrics::Writer &writer) const {
  (*strategy_)(writer);
}

// algo::strategy::Dispatcher

void Strategy::send(CreateOrder const &create_order, uint8_t source, bool is_last) {
  assert(orders_.find(create_order.order_id) == std::end(orders_));  // note! order must not exist
  dispatcher_.send(create_order, source, is_last);                   // note! has priority ==> send before updating the order cache
  cache::Order order{create_order};
  auto res = orders_.emplace(create_order.order_id, std::move(order));
  assert(res.second);
}

void Strategy::send(ModifyOrder const &modify_order, uint8_t source, bool is_last) {
  assert(orders_.find(modify_order.order_id) != std::end(orders_));  // note! order must exist
  dispatcher_.send(modify_order, source, is_last);
}

void Strategy::send(CancelOrder const &cancel_order, uint8_t source, bool is_last) {
  assert(orders_.find(cancel_order.order_id) != std::end(orders_));  // note! order must exist
  dispatcher_.send(cancel_order, source, is_last);
}

void Strategy::send(CancelAllOrders const &cancel_all_orders, uint8_t source) {
  dispatcher_.send(cancel_all_orders, source);
}

void Strategy::send(CustomMetrics const &custom_metrics, uint8_t source) {
  dispatcher_.send(custom_metrics, source);
}

void Strategy::send(CustomMatrix const &custom_matrix, uint8_t source) {
  dispatcher_.send(custom_matrix, source);
}

// algo::OrderCache

cache::Order *Strategy::get_order_helper(uint64_t order_id) {
  auto iter = orders_.find(order_id);
  if (iter != std::end(orders_))
    return &(*iter).second;
  return nullptr;
}

uint64_t Strategy::get_next_trade_id() {
  return ++next_trade_id_;
}

}  // namespace playground
}  // namespace algo
}  // namespace roq
