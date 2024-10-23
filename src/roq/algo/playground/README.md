# Demo: Arbitrage

> Note!
> Remember to run the gateways with the appropriate flag.
> In particular, run `roq-bybit` with `--api="inverse"`.

## Live

```bash
roq-algo-playground --simulate=false --parameters "max_age=10s;threshold=5;quantity_0=1;min_position_0=-5;max_position_0=5" \
  --name "trader" \
  --config_file "test.toml" \
  deribit.sock \
  bybit.sock
```

## Simulate

```bash
roq-algo-playground --simulate=true --parameters "max_age=10s;threshold=5;quantity_0=1;min_position_0=-5;max_position_0=5" \
  --name "trader" \
  --config_file "test.toml" \
  deribit-public.roq \
  bybit-public.roq
```

Which could generate an output like this

```
source: 0
  exchange: deribit
    symbol: BTC-PERPETUAL
      market_data
        reference_data
          total_count: 1
        market_status
          total_count: 1
        top_of_book
          total_count: 10424
        market_by_price_update
          total_count: 92179
        market_by_order_update
          total_count: 0
        trade_summary
          total_count: 316
        statistics_update
          total_count: 1281
      order_management
        order_ack
          accepted_count: 20
          rejected_count: 0
        order_update
          buy_count: 10
          sell_count: 10
          total_count: 20
        trade_update
          fills
            buy_count: 10
            sell_count: 10
            total_count: 20
            buy_volume: 10
            sell_volume: 10
            total_volume: 20
        position_update
          total_count: 20
          position_min: nan
          position_max: 1
        history
          sample_period_utc: 1729515420000000000ns
            best_bid_price: 68175
            best_ask_price: 68175.5
            position: 0
            realized_profit: 0
            unrealized_profit: 0
            average_cost_price: nan
            mark_price: nan
            buy_volume: 0
            sell_volume: 0
            total_volume: 0
          sample_period_utc: 1729515480000000000ns
            best_bid_price: 68201.5
            best_ask_price: 68202
            position: -2
            realized_profit: 0
            unrealized_profit: -42
            average_cost_price: 68181
            mark_price: 68202
            buy_volume: 0
            sell_volume: 2
            total_volume: 2
          sample_period_utc: 1729515540000000000ns
            best_bid_price: 68208
            best_ask_price: 68208.5
            position: -2
            realized_profit: 0
            unrealized_profit: -55
            average_cost_price: 68181
            mark_price: 68208.5
            buy_volume: 0
            sell_volume: 2
            total_volume: 2
          sample_period_utc: 1729515600000000000ns
            best_bid_price: 68165
            best_ask_price: 68165.5
            position: -2
            realized_profit: 0
            unrealized_profit: 31
            average_cost_price: 68181
            mark_price: 68165.5
            buy_volume: 0
            sell_volume: 2
            total_volume: 2
          sample_period_utc: 1729515660000000000ns
            best_bid_price: 68177
            best_ask_price: 68177.5
            position: 0
            realized_profit: 47
            unrealized_profit: 0
            average_cost_price: nan
            mark_price: nan
            buy_volume: 2
            sell_volume: 2
            total_volume: 4
          sample_period_utc: 1729515720000000000ns
            best_bid_price: 68178.5
            best_ask_price: 68179
            position: 0
            realized_profit: 70
            unrealized_profit: 0
            average_cost_price: nan
            mark_price: nan
            buy_volume: 6
            sell_volume: 6
            total_volume: 12
          sample_period_utc: 1729515780000000000ns
            best_bid_price: 68225.5
            best_ask_price: 68226
            position: 0
            realized_profit: 70
            unrealized_profit: 0
            average_cost_price: nan
            mark_price: nan
            buy_volume: 6
            sell_volume: 6
            total_volume: 12
          sample_period_utc: 1729515840000000000ns
            best_bid_price: 68221
            best_ask_price: 68221.5
            position: 0
            realized_profit: 70
            unrealized_profit: 0
            average_cost_price: nan
            mark_price: nan
            buy_volume: 6
            sell_volume: 6
            total_volume: 12
          sample_period_utc: 1729515900000000000ns
            best_bid_price: 68179
            best_ask_price: 68179.5
            position: -2
            realized_profit: 70
            unrealized_profit: 69
            average_cost_price: 68214
            mark_price: 68179.5
            buy_volume: 6
            sell_volume: 8
            total_volume: 14
          sample_period_utc: 1729515960000000000ns
            best_bid_price: 68152
            best_ask_price: 68152.5
            position: 0
            realized_profit: 140
            unrealized_profit: 0
            average_cost_price: nan
            mark_price: nan
            buy_volume: 8
            sell_volume: 8
            total_volume: 16
          sample_period_utc: 1729516020000000000ns
            best_bid_price: 68096
            best_ask_price: 68096.5
            position: 0
            realized_profit: 256
            unrealized_profit: 0
            average_cost_price: nan
            mark_price: nan
            buy_volume: 10
            sell_volume: 10
            total_volume: 20
source: 1
  exchange: bybit
    symbol: BTCUSD
      market_data
        reference_data
          total_count: 1
        market_status
          total_count: 1
        top_of_book
          total_count: 2308
        market_by_price_update
          total_count: 29752
        market_by_order_update
          total_count: 0
        trade_summary
          total_count: 218
        statistics_update
          total_count: 177
      order_management
        order_ack
          accepted_count: 20
          rejected_count: 0
        order_update
          buy_count: 10
          sell_count: 10
          total_count: 20
        trade_update
          fills
            buy_count: 10
            sell_count: 10
            total_count: 20
            buy_volume: 10
            sell_volume: 10
            total_volume: 20
        position_update
          total_count: 20
          position_min: nan
          position_max: 1
        history
          sample_period_utc: 1729515420000000000ns
            best_bid_price: 68170
            best_ask_price: 68170.5
            position: 0
            realized_profit: 0
            unrealized_profit: 0
            average_cost_price: nan
            mark_price: nan
            buy_volume: 0
            sell_volume: 0
            total_volume: 0
          sample_period_utc: 1729515480000000000ns
            best_bid_price: 68193.5
            best_ask_price: 68194
            position: 2
            realized_profit: 0
            unrealized_profit: 46
            average_cost_price: 68170.5
            mark_price: 68193.5
            buy_volume: 2
            sell_volume: 0
            total_volume: 2
          sample_period_utc: 1729515540000000000ns
            best_bid_price: 68194.5
            best_ask_price: 68195
            position: 2
            realized_profit: 0
            unrealized_profit: 48
            average_cost_price: 68170.5
            mark_price: 68194.5
            buy_volume: 2
            sell_volume: 0
            total_volume: 2
          sample_period_utc: 1729515600000000000ns
            best_bid_price: 68167
            best_ask_price: 68167.5
            position: 2
            realized_profit: 0
            unrealized_profit: -7
            average_cost_price: 68170.5
            mark_price: 68167
            buy_volume: 2
            sell_volume: 0
            total_volume: 2
          sample_period_utc: 1729515660000000000ns
            best_bid_price: 68172
            best_ask_price: 68172.5
            position: 0
            realized_profit: -3
            unrealized_profit: 0
            average_cost_price: nan
            mark_price: nan
            buy_volume: 2
            sell_volume: 2
            total_volume: 4
          sample_period_utc: 1729515720000000000ns
            best_bid_price: 68181
            best_ask_price: 68181.5
            position: 0
            realized_profit: 60
            unrealized_profit: 0
            average_cost_price: nan
            mark_price: nan
            buy_volume: 6
            sell_volume: 6
            total_volume: 12
          sample_period_utc: 1729515780000000000ns
            best_bid_price: 68225.5
            best_ask_price: 68226
            position: 0
            realized_profit: 60
            unrealized_profit: 0
            average_cost_price: nan
            mark_price: nan
            buy_volume: 6
            sell_volume: 6
            total_volume: 12
          sample_period_utc: 1729515840000000000ns
            best_bid_price: 68222
            best_ask_price: 68222.5
            position: 0
            realized_profit: 60
            unrealized_profit: 0
            average_cost_price: nan
            mark_price: nan
            buy_volume: 6
            sell_volume: 6
            total_volume: 12
          sample_period_utc: 1729515900000000000ns
            best_bid_price: 68176
            best_ask_price: 68176.5
            position: 2
            realized_profit: 60
            unrealized_profit: -31
            average_cost_price: 68191.5
            mark_price: 68176
            buy_volume: 8
            sell_volume: 6
            total_volume: 14
          sample_period_utc: 1729515960000000000ns
            best_bid_price: 68149
            best_ask_price: 68149.5
            position: 0
            realized_profit: 58
            unrealized_profit: 0
            average_cost_price: nan
            mark_price: nan
            buy_volume: 8
            sell_volume: 8
            total_volume: 16
          sample_period_utc: 1729516020000000000ns
            best_bid_price: 68103
            best_ask_price: 68103.5
            position: 0
            realized_profit: 1
            unrealized_profit: 0
            average_cost_price: nan
            mark_price: nan
            buy_volume: 10
            sell_volume: 10
            total_volume: 20
```
