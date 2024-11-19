/* Copyright (c) 2017-2025, Hans Erik Thrane */

#pragma once

#include <span>
#include <string_view>

#include "roq/service.hpp"

#include "roq/samples/algo/config.hpp"
#include "roq/samples/algo/factory.hpp"
#include "roq/samples/algo/settings.hpp"

namespace roq {
namespace samples {
namespace algo {

struct Application final : public Service {
  using Service::Service;

 protected:
  int main(args::Parser const &) override;

  void simulate(Settings const &, Factory const &, Config const &, std::span<std::string_view const> const &params);

  void trade(Settings const &, Factory const &, Config const &, std::span<std::string_view const> const &params);
};

}  // namespace algo
}  // namespace samples
}  // namespace roq
