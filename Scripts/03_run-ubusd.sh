#!/bin/bash

# You can run something like this when initializing your ubus socket
export UBUS_SOCKET="$PWD/my_own_socket.sock"
export LD_LIBRARY_PATH="$PWD/../Packages/libubox/build:$PWD/../Packages/ubus/build:$LD_LIBRARY_PATH"
./ubusd -s "$UBUS_SOCKET" &

# Instead of running this shell script, do something like below.
# It is up to you the name of the ubus socket.
# sudo ./ubusd -s my_own_socket.sock &

