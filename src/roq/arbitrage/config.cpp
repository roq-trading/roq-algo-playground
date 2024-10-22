/* Copyright (c) 2017-2024, Hans Erik Thrane */

#include "roq/arbitrage/config.hpp"

#include <toml++/toml.h>

#include "roq/logging.hpp"

using namespace std::literals;

namespace roq {
namespace arbitrage {

// === HELPERS ===

namespace {
template <typename T>
auto parse_enum(auto &value) {
  auto result = magic_enum::enum_cast<T>(value, magic_enum::case_insensitive);
  if (!result.has_value())
    log::fatal(R"(Unexpected: value="{}")"sv, value);
  return result.value();
}

template <typename R>
void constexpr get_helper(R &result, auto &value) {
  using result_type = std::remove_cvref<R>::type;
  if constexpr (std::is_enum<result_type>::value) {
    auto tmp = value.template value<std::string_view>().value();
    result = parse_enum<result_type>(tmp);
  } else {
    result = value.template value<R>().value();
  }
}

template <typename R>
auto parse_legs(auto &array) {
  using result_type = std::remove_cvref<R>::type;
  using value_type = result_type::value_type;
  result_type result;
  enum class Key {
    SOURCE,
    ACCOUNT,
    EXCHANGE,
    SYMBOL,
    TIME_IN_FORCE,
  };
  for (auto &item : array) {
    auto table = item.as_table();
    value_type leg;
    for (auto &[key, value] : *table) {
      auto key_2 = parse_enum<Key>(key);
      switch (key_2) {
        case Key::SOURCE:
          get_helper(leg.source, value);
          break;
        case Key::ACCOUNT:
          get_helper(leg.account, value);
          break;
        case Key::EXCHANGE:
          get_helper(leg.exchange, value);
          break;
        case Key::SYMBOL:
          get_helper(leg.symbol, value);
          break;
        case Key::TIME_IN_FORCE:
          get_helper(leg.time_in_force, value);
          break;
      }
    }
    // XXX TODO validate
    result.emplace_back(std::move(leg));
  }
  return result;
}

// XXX FIXME TODO we're parsing TWO times !!!

template <typename R>
auto create_type(auto &config_file) {
  using result_type = std::remove_cvref<R>::type;
  result_type result = {};
  auto root = toml::parse_file(config_file);
  enum class Key {
    TYPE,
    LEGS,
  };
  for (auto &[key, value] : root) {
    auto key_2 = parse_enum<Key>(key);
    switch (key_2) {
      case Key::TYPE: {
        auto value_2 = value.template value<std::string_view>().value();
        result = parse_enum<result_type>(value_2);
        break;
      }
      case Key::LEGS:
        break;
    }
  }
  return result;
}

template <typename R>
auto create_legs(auto &config_file) {
  using result_type = std::remove_cvref<R>::type;
  result_type result;
  auto root = toml::parse_file(config_file);
  enum class Key {
    TYPE,
    LEGS,
  };
  for (auto &[key, value] : root) {
    auto key_2 = parse_enum<Key>(key);
    switch (key_2) {
      case Key::TYPE:
        break;
      case Key::LEGS:
        result = parse_legs<R>(*value.as_array());
        break;
    }
  }
  return result;
}
}  // namespace

// === IMPLEMENTATION ===

Config::Config(Settings const &settings)
    : settings_{settings}, type{create_type<decltype(type)>(settings.config_file)}, legs{create_legs<decltype(legs)>(settings.config_file)} {
  log::info("config={}"sv, *this);
}

void Config::dispatch(Handler &handler) const {
  // settings
  handler(roq::client::Settings{
      .order_cancel_policy = roq::OrderCancelPolicy::BY_ACCOUNT,
      .order_management = {},
  });
  // accounts
  for (auto &item : legs) {
    client::Account account{.regex = item.account};
    handler(account);
  }
  // symbols
  for (auto &item : legs) {
    client::Symbol symbol{
        .regex = item.symbol,
        .exchange = item.exchange,
    };
    handler(symbol);
  }
}

}  // namespace arbitrage
}  // namespace roq
