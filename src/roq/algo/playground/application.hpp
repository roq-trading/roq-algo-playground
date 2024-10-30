/* Copyright (c) 2017-2024, Hans Erik Thrane */

#pragma once

#include <span>
#include <string_view>

#include "roq/service.hpp"

#include "roq/algo/strategy/config.hpp"

#include "roq/algo/playground/factory.hpp"
#include "roq/algo/playground/settings.hpp"

namespace roq {
namespace algo {
namespace playground {

struct Application final : public roq::Service {
  using Service::Service;

 protected:
  int main(roq::args::Parser const &) override;

  void simulation(Settings const &, Factory const &, algo::strategy::Config const &, std::span<std::string_view const> const &params);

  void trading(Settings const &, Factory const &, algo::strategy::Config const &, std::span<std::string_view const> const &params);
};

}  // namespace playground
}  // namespace algo
}  // namespace roq
