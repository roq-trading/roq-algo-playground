#!/usr/bin/env bash

NAME="trader"

CONFIG_FILE="test.toml"

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

$PREFIX "./roq-algo-playground" \
  --name "$NAME" \
  --config_file "$CONFIG_FILE" \
  $@
