#!/usr/bin/env python

import os
import datetime

from types import SimpleNamespace

import pandas as pd

import roq


settings = roq.client.Settings2(
    app={
        "name": "trader",
    },
    loop={
        "timer_freq": datetime.timedelta(milliseconds=100),
    },
    service={},
    common={},
)


config = roq.algo.strategy.Config(
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


factory = dict(
    create_strategy=lambda dispatcher, config: roq.algo.strateg.create(
        type=config.strategy.type,
        config=config,
        parameters="max_age=10s;threshold=5;quantity_0=1;min_position_0=-5;max_position_0=5",
    ),
    create_reporter=lambda: roq.algo.reporter.create(
        type=roq.algo.reporter.Type.SUMMARY,
    ),
    create_matcher=lambda dispatcher, source, exchange, symbol: None,
)


parameters = [
    "{HOME}/var/lib/roq/data/deribit-public.roq".format(**os.environ),
    "{HOME}/var/lib/roq/data/bybit-public.roq".format(**os.environ),
]


reporter = roq.client.Simulator2.dispatch(
    settings=settings,
    factory=factory,
    config=config,
    parameters=parameters,
)


result = reporter.extract("history")
print(result)


df = pd.DataFrame(result["data"]).set_index(result["index"])
print(df)
