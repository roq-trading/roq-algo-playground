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

The `Summary` reporter can be configured for different output styles.

Using `--simulation_reporter_output_type=TEXT`

```yaml
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

Using `--simulation_reporter_output_type=CSV` and `--simulation_reporter_label=history`

```csv
source,exchange,symbol,datetime,best_bid_price,best_ask_price,position,realized_profit,unrealized_profit,average_cost_price,mark_price,buy_volume,sell_volume,total_volume
0,deribit,BTC-PERPETUAL,1729515420000000000ns,68175,68175.5,0,0,0,nan,nan,0,0,0
0,deribit,BTC-PERPETUAL,1729515480000000000ns,68201.5,68202,-2,0,-42,68181,68202,0,2,2
0,deribit,BTC-PERPETUAL,1729515540000000000ns,68208,68208.5,-2,0,-55,68181,68208.5,0,2,2
0,deribit,BTC-PERPETUAL,1729515600000000000ns,68165,68165.5,-2,0,31,68181,68165.5,0,2,2
0,deribit,BTC-PERPETUAL,1729515660000000000ns,68177,68177.5,0,47,0,nan,nan,2,2,4
0,deribit,BTC-PERPETUAL,1729515720000000000ns,68178.5,68179,0,70,0,nan,nan,6,6,12
0,deribit,BTC-PERPETUAL,1729515780000000000ns,68225.5,68226,0,70,0,nan,nan,6,6,12
0,deribit,BTC-PERPETUAL,1729515840000000000ns,68221,68221.5,0,70,0,nan,nan,6,6,12
0,deribit,BTC-PERPETUAL,1729515900000000000ns,68179,68179.5,-2,70,69,68214,68179.5,6,8,14
0,deribit,BTC-PERPETUAL,1729515960000000000ns,68152,68152.5,0,140,0,nan,nan,8,8,16
0,deribit,BTC-PERPETUAL,1729516020000000000ns,68096,68096.5,0,256,0,nan,nan,10,10,20
1,bybit,BTCUSD,1729515420000000000ns,68170,68170.5,0,0,0,nan,nan,0,0,0
1,bybit,BTCUSD,1729515480000000000ns,68193.5,68194,2,0,46,68170.5,68193.5,2,0,2
1,bybit,BTCUSD,1729515540000000000ns,68194.5,68195,2,0,48,68170.5,68194.5,2,0,2
1,bybit,BTCUSD,1729515600000000000ns,68167,68167.5,2,0,-7,68170.5,68167,2,0,2
1,bybit,BTCUSD,1729515660000000000ns,68172,68172.5,0,-3,0,nan,nan,2,2,4
1,bybit,BTCUSD,1729515720000000000ns,68181,68181.5,0,60,0,nan,nan,6,6,12
1,bybit,BTCUSD,1729515780000000000ns,68225.5,68226,0,60,0,nan,nan,6,6,12
1,bybit,BTCUSD,1729515840000000000ns,68222,68222.5,0,60,0,nan,nan,6,6,12
1,bybit,BTCUSD,1729515900000000000ns,68176,68176.5,2,60,-31,68191.5,68176,8,6,14
1,bybit,BTCUSD,1729515960000000000ns,68149,68149.5,0,58,0,nan,nan,8,8,16
1,bybit,BTCUSD,1729516020000000000ns,68103,68103.5,0,1,0,nan,nan,10,10,20
```
