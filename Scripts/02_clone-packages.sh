#!/bin/bash

set -e

# Root and Packages directory
ROOT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")/.." && pwd)"
PACKAGES_DIR="$ROOT_DIR/Packages"
mkdir -p "$PACKAGES_DIR"
cd "$PACKAGES_DIR"

# Git repo URLs
JSON_C_REPO="https://github.com/json-c/json-c.git"
LIBUBOX_REPO="https://git.openwrt.org/project/libubox.git"
UBUS_REPO="https://git.openwrt.org/project/ubus.git"

# Clone json-c
if [ ! -d "json-c" ]; then
    git clone "$JSON_C_REPO"
else
    echo "[INFO] json-c already exists, skipping..."
fi

# Clone libubox
if [ ! -d "libubox" ]; then
    git clone "$LIBUBOX_REPO"
else
    echo "[INFO] libubox already exists, skipping..."
fi

# Clone ubus
if [ ! -d "ubus" ]; then
    git clone "$UBUS_REPO"
else
    echo "[INFO] ubus already exists, skipping..."
fi

echo "✅ All packages cloned into: $PACKAGES_DIR"

