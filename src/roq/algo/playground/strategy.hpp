/* Copyright (c) 2017-2024, Hans Erik Thrane */

#pragma once

#include "roq/utils/container.hpp"

#include "roq/cache/order.hpp"

#include "roq/algo/order_cache.hpp"

#include "roq/algo/strategy/dispatcher.hpp"
#include "roq/algo/strategy/handler.hpp"

#include "roq/client.hpp"

#include "roq/algo/playground/config.hpp"
#include "roq/algo/playground/settings.hpp"

namespace roq {
namespace algo {
namespace playground {

struct Strategy final : public client::Handler, public algo::strategy::Dispatcher, public algo::OrderCache {
  Strategy(roq::client::Dispatcher &, Settings const &, Config const &);

  Strategy(Strategy &&) = default;
  Strategy(Strategy const &) = delete;

 protected:
  // client::Handler

  // host
  void operator()(Event<Start> const &) override;
  void operator()(Event<Stop> const &) override;
  void operator()(Event<Timer> const &) override;
  void operator()(Event<Connected> const &) override;
  void operator()(Event<Disconnected> const &) override;

  // control
  void operator()(Event<DownloadBegin> const &) override;
  void operator()(Event<DownloadEnd> const &) override;
  void operator()(Event<Ready> const &) override;

  // config
  void operator()(Event<GatewaySettings> const &) override;

  // stream
  void operator()(Event<StreamStatus> const &) override;
  void operator()(Event<ExternalLatency> const &) override;
  void operator()(Event<RateLimitsUpdate> const &) override;
  void operator()(Event<RateLimitTrigger> const &) override;

  // service
  void operator()(Event<GatewayStatus> const &) override;

  // market data
  void operator()(Event<ReferenceData> const &) override;
  void operator()(Event<MarketStatus> const &) override;
  void operator()(Event<TopOfBook> const &) override;
  void operator()(Event<MarketByPriceUpdate> const &) override;
  void operator()(Event<MarketByOrderUpdate> const &) override;
  void operator()(Event<TradeSummary> const &) override;
  void operator()(Event<StatisticsUpdate> const &) override;

  // market data (derived)
  void operator()(Event<TimeSeriesUpdate> const &) override;

  // order management
  void operator()(Event<CancelAllOrdersAck> const &) override;
  void operator()(Event<OrderAck> const &) override;
  void operator()(Event<OrderUpdate> const &) override;
  void operator()(Event<TradeUpdate> const &) override;

  // account management (exchange)
  void operator()(Event<PositionUpdate> const &) override;
  void operator()(Event<FundsUpdate> const &) override;

  // parameters
  void operator()(Event<ParametersUpdate> const &) override;

  // position manager (service)
  void operator()(Event<PortfolioUpdate> const &) override;

  // risk managemenet
  void operator()(Event<RiskLimitsUpdate> const &) override;

  // metrics
  void operator()(metrics::Writer &) const override;

  // algo::strategy::Dispatcher

  void send(CreateOrder const &, uint8_t source, bool is_last) override;
  void send(ModifyOrder const &, uint8_t source, bool is_last) override;
  void send(CancelOrder const &, uint8_t source, bool is_last) override;

  void send(CancelAllOrders const &, uint8_t source) override;

  void send(CustomMetrics const &, uint8_t source) override;
  void send(CustomMatrix const &, uint8_t source) override;

  // algo::OrderCache

  cache::Order *get_order_helper(uint64_t order_id) override;

  uint64_t get_next_trade_id() override;

 private:
  roq::client::Dispatcher &dispatcher_;
  utils::unordered_map<uint64_t, cache::Order> orders_;
  std::unique_ptr<algo::strategy::Handler> strategy_;
  uint64_t next_trade_id_ = {};
};

}  // namespace playground
}  // namespace algo
}  // namespace roq
