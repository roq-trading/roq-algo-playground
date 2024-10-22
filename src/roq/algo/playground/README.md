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
          accepted_count: 136
          rejected_count: 0
        order_update
          buy_count: 70
          sell_count: 68
          total_count: 138
        trade_update
          fills
            buy_count: 70
            sell_count: 66
            total_count: 136
            buy_volume: 70
            sell_volume: 66
            total_volume: 136
        position_update
          total_count: 136
          position_min: nan
          position_max: 5
        history
          sample_period_utc: 1729515420000000000ns
            price: 68175.25
            position: 0
            profit: 0
          sample_period_utc: 1729515480000000000ns
            price: 68201.75
            position: -6
            profit: -154.5
          sample_period_utc: 1729515540000000000ns
            price: 68208.25
            position: -6
            profit: -193.5
          sample_period_utc: 1729515600000000000ns
            price: 68165.25
            position: -6
            profit: 64.5
          sample_period_utc: 1729515660000000000ns
            price: 68177.25
            position: 4
            profit: 190
          sample_period_utc: 1729515720000000000ns
            price: 68178.75
            position: 4
            profit: 311
          sample_period_utc: 1729515780000000000ns
            price: 68225.75
            position: 4
            profit: 494
          sample_period_utc: 1729515840000000000ns
            price: 68221.25
            position: 4
            profit: 476
          sample_period_utc: 1729515900000000000ns
            price: 68179.25
            position: 0
            profit: 631.5
          sample_period_utc: 1729515960000000000ns
            price: 68152.25
            position: -6
            profit: 602
          sample_period_utc: 1729516020000000000ns
            price: 68096.25
            position: 4
            profit: 917.5
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
          accepted_count: 136
          rejected_count: 0
        order_update
          buy_count: 66
          sell_count: 71
          total_count: 137
        trade_update
          fills
            buy_count: 66
            sell_count: 70
            total_count: 136
            buy_volume: 66
            sell_volume: 70
            total_volume: 136
        position_update
          total_count: 136
          position_min: nan
          position_max: 5
        history
          sample_period_utc: 1729515420000000000ns
            price: 68170.25
            position: 0
            profit: 0
          sample_period_utc: 1729515480000000000ns
            price: 68193.75
            position: 6
            profit: 139.5
          sample_period_utc: 1729515540000000000ns
            price: 68194.75
            position: 6
            profit: 145.5
          sample_period_utc: 1729515600000000000ns
            price: 68167.25
            position: 6
            profit: -19.5
          sample_period_utc: 1729515660000000000ns
            price: 68172.25
            position: -4
            profit: -52
          sample_period_utc: 1729515720000000000ns
            price: 68181.25
            position: -4
            profit: 119.5
          sample_period_utc: 1729515780000000000ns
            price: 68225.75
            position: -4
            profit: 128.5
          sample_period_utc: 1729515840000000000ns
            price: 68222.25
            position: -4
            profit: 142.5
          sample_period_utc: 1729515900000000000ns
            price: 68176.25
            position: 0
            profit: 201
          sample_period_utc: 1729515960000000000ns
            price: 68149.25
            position: 6
            profit: 299.5
          sample_period_utc: 1729516020000000000ns
            price: 68103.25
            position: -4
            profit: 210
```
