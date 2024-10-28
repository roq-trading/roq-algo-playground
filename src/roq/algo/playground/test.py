#!/usr/bin/env python

import datetime
import roq


def create_legs():
    leg_1 = roq.algo.Leg(
        source=0,
        account="A1",
        exchange="deribit",
        symbol="BTC-PERPETUAL",
        time_in_force=roq.TimeInForce.GTC,
    )
    leg_2 = roq.algo.Leg(
        source=1,
        account="A2",
        exchange="bybit",
        symbol="BTC-PERPETUAL",
        time_in_force=roq.TimeInForce.GTC,
    )
    return [leg_1, leg_2]


def create_strategy():
    legs = create_legs()
    config = roq.algo.strategy.Config(legs=legs, strategy_id=123)
    parameters = (
        "max_age=10s;threshold=5;quantity_0=1;min_position_0=-5;max_position_0=5"
    )
    strategy = roq.algo.Strategy(roq.algo.strategy.Type.ARBITRAGE, config, parameters)
    return strategy


def create_reporter():
    reporter = roq.algo.Reporter(type=roq.algo.reporter.Type.SUMMARY)
    return reporter


def create_summary_reporter():
    reporter = roq.algo.reporter.Summary(
        market_data_source=roq.algo.MarketDataSource.TOP_OF_BOOK,
        sample_frequency=datetime.timedelta(seconds=60),
    )
    return reporter


strategy = create_strategy()
print(strategy)

reporter = create_reporter()
print(reporter)

summary_reporter = create_summary_reporter()
print(summary_reporter)
