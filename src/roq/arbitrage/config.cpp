/* Copyright (c) 2017-2024, Hans Erik Thrane */

#include "roq/arbitrage/config.hpp"

#include "roq/logging.hpp"

using namespace std::literals;

namespace roq {
namespace arbitrage {

Config::Config(Settings const &settings) : settings_{settings} {
}

void Config::dispatch(Handler &handler) const {
  // settings
  handler(roq::client::Settings{
      .order_cancel_policy = roq::OrderCancelPolicy::BY_ACCOUNT,
      .order_management = {},
  });
  // accounts
  for (auto &item : settings_.accounts) {
    client::Account account{.regex = item};
    handler(account);
  }
  // symbols
  auto size = std::size(settings_.symbols);
  if (std::size(settings_.exchanges) != size)
    log::fatal("Unexpected: mismatched size: exchanges=[{}], symbols=[{}]"sv, fmt::join(settings_.exchanges, ", "sv), fmt::join(settings_.symbols, ", "sv));
  for (size_t i = 0; i < size; ++i) {
    client::Symbol symbol{
        .regex = settings_.symbols[i],
        .exchange = settings_.exchanges[i],
    };
    handler(symbol);
  }
}

}  // namespace arbitrage
}  // namespace roq
