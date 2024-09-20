#!/usr/bin/env bash

NAME="trader"

ACCOUNTS="A1,A1"
EXCHANGES="deribit,bybit"
SYMBOLS="BTC-PERPETUAL,BTCUSDT"

if [ "$1" == "debug" ]; then
  case "$KERNEL" in
    Linux*)
      PREFIX="gdb --command=gdb_commands --args"
      ;;
    Darwin*)
      PREFIX="lldb --"
      ;;
  esac
  shift 1
else
  PREFIX=
fi

$PREFIX "./roq-algo-playground-arbitrage" \
  --name "$NAME" \
  --accounts "$ACCOUNTS" \
  --exchanges "$EXCHANGES" \
  --symbols "$SYMBOLS" \
  $@
