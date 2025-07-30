# Directories
PKG_DIR ?= ../Packages
OUTPUT_DIR ?= ..

# Library build directories
LIBUBOX_BUILD := $(PKG_DIR)/libubox/build
UBUS_BUILD := $(PKG_DIR)/ubus/build

# Compiler and flags
CC := gcc
CFLAGS := \
  -I$(PKG_DIR)/json-c/include \
  -I$(PKG_DIR)/libubox/include \
  -I$(PKG_DIR)/ubus \
  -I$(PKG_DIR)/libubox \
  -I$(PKG_DIR)

LDFLAGS := \
  -L$(LIBUBOX_BUILD) -lubox -lblobmsg_json \
  -L$(UBUS_BUILD) -lubus -lrt

# Source files and target
TARGET := hello_service
SRC := hello_service.c
OUT := $(OUTPUT_DIR)/$(TARGET)

# Default target
all: $(OUT)

$(OUT): $(SRC)
	$(CC) -o $@ $^ $(CFLAGS) $(LDFLAGS)

# Clean up
clean:
	rm -f $(OUT)

