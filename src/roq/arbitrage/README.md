# Demo: Arbitrage

> Note! Remember to run the gateways with the appropriate flag (`roq-bybit` with `--api="linear"`).

## Live

```bash
roq-algo-playground-arbitrage --simulate=false --model_threshold=5 --model_quantity_0=1 --model_min_position_0=-5 --model_max_position_0=5 \
  --name "trader" \
  --accounts "A1,A1"
  --exchanges "deribit,bybit" \
  --symbols "BTC-PERPETUAL,BTCUSDT" \
  deribit.sock \
  bybit.sock
```

## Simulate

```bash
roq-algo-playground-arbitrage --simulate=true --model_threshold=5 --model_quantity_0=1 --model_min_position_0=-5 --model_max_position_0=5 \
  --name "trader" \
  --accounts "A1,A1"
  --exchanges "deribit,bybit" \
  --symbols "BTC-PERPETUAL,BTCUSDT" \
  deribit-public.roq \
  bybit-public.roq
```
