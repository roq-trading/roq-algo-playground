#!/usr/bin/env python

import os
import datetime

import pandas as pd

import roq


SETTINGS = roq.client.Settings2(
    app={
        "name": "trader",
    },
    loop={
        "timer_freq": datetime.timedelta(milliseconds=100),
    },
    service={},
    common={},
)


CONFIG = roq.algo.strategy.Config(
    legs=[
        roq.algo.Leg(
            source=0,
            account="A1",
            exchange="deribit",
            symbol="BTC-PERPETUAL",
            time_in_force=roq.TimeInForce.GTC,
        ),
        roq.algo.Leg(
            source=1,
            account="A1",
            exchange="bybit",
            symbol="BTCUSD",
        ),
    ],
    strategy_id=123,
)


def create_strategy(dispatcher, order_cache, config):
    return roq.algo.strategy.create(
        type=roq.algo.strategy.Type.ARBITRAGE,
        dispatcher=dispatcher,
        order_cache=order_cache,
        config=config,
        parameters="max_age=10s;threshold=5;quantity_0=1;min_position_0=-5;max_position_0=5",
    )


def create_reporter():
    return roq.algo.reporter.create(
        type=roq.algo.reporter.Type.SUMMARY,
    )


def create_matcher(dispatcher, order_cache, config):
    return roq.algo.matcher.create(
        type=roq.algo.matcher.Type.SIMPLE,
        dispatcher=dispatcher,
        order_cache=order_cache,
        config=config,
    )


FACTORY = roq.algo.Factory(
    create_strategy=create_strategy,
    create_reporter=create_reporter,
    create_matcher=create_matcher,
)


PARAMETERS = [
    "{HOME}/var/lib/roq/data/deribit-public.roq".format(**os.environ),
    "{HOME}/var/lib/roq/data/bybit-public.roq".format(**os.environ),
]


reporter = roq.client.Simulator2.dispatch(
    settings=SETTINGS,
    factory=FACTORY,
    config=CONFIG,
    parameters=PARAMETERS,
)


result = reporter.extract("history")
print(result)


df = pd.DataFrame(result["data"]).set_index(result["index"])
print(df)
