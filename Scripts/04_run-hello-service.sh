#!/bin/bash
export LD_LIBRARY_PATH="$PWD/../Packages/libubox/build:$PWD/../Packages/ubus/build:$LD_LIBRARY_PATH"

./hello-service &

