#!/bin/bash
export LD_LIBRARY_PATH="$PWD/../Packages/libubox/build:$PWD/../Packages/ubus/build:$LD_LIBRARY_PATH"
export UBUS_SOCKET="$PWD/hm.sock"

./hello_service

