#!/bin/bash
export UBUS_SOCKET="$PWD/hm.sock"
export LD_LIBRARY_PATH="$PWD/../Packages/libubox/build:$PWD/../Packages/ubus/build:$LD_LIBRARY_PATH"
./ubusd -s "$UBUS_SOCKET" &

