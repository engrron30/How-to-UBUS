#!/bin/bash

# List of required packages
packages=(
    build-essential
    git
    libjson-c-dev
    libblobmsg-json-dev
    pkg-config
)

# Function to check if a package is installed
is_installed() {
    dpkg -s "$1" &> /dev/null
}

# Gather missing packages
missing=()
for pkg in "${packages[@]}"; do
    echo -n "Checking $pkg... "
    if is_installed "$pkg"; then
        echo "already installed."
    else
        echo "missing."
        missing+=("$pkg")
    fi
done

# Install missing packages if any
if [ ${#missing[@]} -ne 0 ]; then
    echo "Updating package list..."
    sudo apt update

    echo "Installing missing packages: ${missing[*]}"
    sudo apt install -y "${missing[@]}"
else
    echo "All packages are already installed."
fi

