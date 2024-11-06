/* Copyright (c) 2017-2024, Hans Erik Thrane */

#pragma once

#include <span>
#include <string_view>

#include "roq/service.hpp"

#include "roq/algo/strategy/config.hpp"

#include "roq/samples/algo/factory.hpp"
#include "roq/samples/algo/settings.hpp"

namespace roq {
namespace samples {
namespace algo {

struct Application final : public Service {
  using Service::Service;

 protected:
  int main(args::Parser const &) override;

  void simulation(Settings const &, Factory const &, roq::algo::strategy::Config const &, std::span<std::string_view const> const &params);

  void trading(Settings const &, Factory const &, roq::algo::strategy::Config const &, std::span<std::string_view const> const &params);
};

}  // namespace algo
}  // namespace samples
}  // namespace roq
