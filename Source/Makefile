# Directories
TOP_DIR ?= $(CURDIR)/..
PKG_DIR ?= $(TOP_DIR)/Packages
SRC_DIR ?= $(TOP_DIR)/Source
SCR_DIR ?= $(TOP_DIR)/Scripts
INC_DIR := $(TOP_DIR)/Include

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
  -I$(PKG_DIR) \
  -I$(INC_DIR)

LDFLAGS := \
  -L$(LIBUBOX_BUILD) -lubox -lblobmsg_json \
  -L$(UBUS_BUILD) -lubus -lrt

# Source files and target
TARGET := hello_service
SRCS := $(wildcard $(SRC_DIR)/*.c)
OBJS := $(SRCS:$(SRC_DIR)/%.c=%.o)


all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) -o $@ $^ $(CFLAGS) $(LDFLAGS)

%.o: $(SRC_DIR)/%.c
	$(CC) -c -o $@ $< $(CFLAGS)

# Clean up
clean:
	rm -f $(OUT)

