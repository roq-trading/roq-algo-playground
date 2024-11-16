#!/usr/bin/env bash

NAME="trader"

STRATEGY_CONFIG_FILE="strategy.toml"
SIMULATOR_CONFIG_FILE="simulator.toml"

KERNEL="$(uname -a)"

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

$PREFIX "./roq-cpp-algo-template" \
  --name "$NAME" \
  --strategy_config_file "$STRATEGY_CONFIG_FILE" \
  --simulator_config_file "$SIMULATOR_CONFIG_FILE" \
  $@
