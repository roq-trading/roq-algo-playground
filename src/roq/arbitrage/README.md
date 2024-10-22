# Demo: Arbitrage

> Note!
> Remember to run the gateways with the appropriate flag.
> In particular, run `roq-bybit` with `--api="inverse"`.

## Live

```bash
roq-algo-playground-arbitrage --simulate=false --parameters "max_age=10s;threshold=5;quantity_0=1;min_position_0=-5;max_position_0=5" \
  --name "trader" \
  --config_file "test.toml" \
  deribit.sock \
  bybit.sock
```

## Simulate

```bash
roq-algo-playground-arbitrage --simulate=true --parameters "max_age=10s;threshold=5;quantity_0=1;min_position_0=-5;max_position_0=5" \
  --name "trader" \
  --config_file "test.toml" \
  deribit-public.roq \
  bybit-public.roq
```
