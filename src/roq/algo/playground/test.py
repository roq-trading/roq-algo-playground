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
        account="A1",
        exchange="bybit",
        symbol="BTCUSD",
        time_in_force=roq.TimeInForce.GTC,
    )
    result = [leg_1, leg_2]
    return result


def create_strategy():
    legs = create_legs()
    config = roq.algo.strategy.Config(legs=legs, strategy_id=123)
    parameters = (
        "max_age=10s;threshold=5;quantity_0=1;min_position_0=-5;max_position_0=5"
    )
    result = roq.algo.strategy.create(roq.algo.strategy.Type.ARBITRAGE, config, parameters)
    return result


def create_arbitrage_strategy():
    legs = create_legs()
    config = roq.algo.strategy.Config(legs=legs, strategy_id=123)
    parameters = (
        "max_age=10s;threshold=5;quantity_0=1;min_position_0=-5;max_position_0=5"
    )
    result = roq.algo.arbitrage.create(config, parameters)
    return result



def create_reporter():
    result = roq.algo.reporter.create(type=roq.algo.reporter.Type.SUMMARY)
    return result


def create_summary_reporter():
    result = roq.algo.reporter.Summary.create(
        market_data_source=roq.algo.MarketDataSource.TOP_OF_BOOK,
        sample_frequency=datetime.timedelta(seconds=60),
    )
    return result


strategy = create_strategy()
print(strategy)
# TODO: print schema

arbitrage_strategy = create_arbitrage_strategy()
print(arbitrage_strategy)
# TODO: print schema

reporter = create_reporter()
print(reporter)
# TODO: extract result data

summary_reporter = create_summary_reporter()
print(summary_reporter)
# TODO: extract result data
