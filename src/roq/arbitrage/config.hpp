/* Copyright (c) 2017-2024, Hans Erik Thrane */

#pragma once

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
};

}  // namespace arbitrage
}  // namespace roq
