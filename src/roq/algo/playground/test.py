#!/usr/bin/env python

import os
import datetime

from types import SimpleNamespace

import pandas as pd

import roq


CONFIG = SimpleNamespace(
    strategy=SimpleNamespace(
        type=roq.algo.strategy.Type.ARBITRAGE,
        parameters="max_age=10s;threshold=5;quantity_0=1;min_position_0=-5;max_position_0=5",
        strategy_id=123,
        legs=[
            dict(
                source=0,
                account="A1",
                exchange="deribit",
                symbol="BTC-PERPETUAL",
                time_in_force=roq.TimeInForce.GTC,
            ),
            dict(
                source=1,
                account="A1",
                exchange="bybit",
                symbol="BTCUSD",
            ),
        ],
    ),
    reporter=SimpleNamespace(
        type=roq.algo.reporter.Type.SUMMARY,
        output_type=roq.algo.reporter.OutputType.JSON,
    ),
)


PARAMS = [
    "{HOME}/var/lib/roq/data/deribit-public.roq".format(**os.environ),
    "{HOME}/var/lib/roq/data/bybit-public.roq".format(**os.environ),
]


####################################


def create_settings():
    result = roq.client.Settings2(
        app={
            "name": "trader",
        },
        loop={
            "timer_freq": datetime.timedelta(milliseconds=100),
        },
        service={},
        common={},
    )
    return result


def create_legs():
    result = []
    for item in CONFIG.strategy.legs:
        leg = roq.algo.Leg(**item)
        result.append(leg)
    return result


def create_config():
    legs = create_legs()
    result = roq.algo.strategy.Config(
        legs=legs,
        strategy_id=CONFIG.strategy.strategy_id,
    )
    return result


def create_strategy():
    config = create_config()
    result = roq.algo.strategy.create(
        type=CONFIG.strategy.type,
        config=config,
        parameters=CONFIG.strategy.parameters,
    )
    return result


def create_arbitrage_strategy():
    config = create_config()
    result = roq.algo.arbitrage.create(
        config=config,
        parameters=CONFIG.strategy.parameters,
    )
    return result


def create_reporter():
    result = roq.algo.reporter.create(
        type=CONFIG.reporter.type,
    )
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


####################################


settings = create_settings()
print(settings)

factory = dict(
    create_strategy=lambda dispatcher, config: roq.algo.strateg.create(
        type=CONFIG.strategy.type,
        config=config,
        parameters=CONFIG.strategy.parameters,
    ),
    create_reporter=lambda: roq.algo.reporter.create(
        type=CONFIG.reporter.type,
    ),
    create_matcher=lambda dispatcher, source, exchange, symbol: None,
)
print(factory)

config = create_config()
print(config)

reporter = roq.client.Simulator2.dispatch(
    settings=settings,
    factory=factory,
    config=config,
    parameters=PARAMS,
)
print(reporter)

data = reporter.extract("history")
print(data)

df = pd.DataFrame(data)
print(df)
