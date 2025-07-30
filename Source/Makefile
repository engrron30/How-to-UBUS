PKG_DIR ?= ../Packages
OUTPUT_DIR ?= ..

LIBUBOX_BUILD := $(PKG_DIR)/libubox/build
UBUS_BUILD := $(PKG_DIR)/ubus/build

CC := gcc
CFLAGS := \
  -I$(PKG_DIR)/json-c/include \
  -I$(PKG_DIR)/libubox/include \
  -I$(PKG_DIR)/ubus \
  -I$(PKG_DIR)/libubox
LDFLAGS := \
  -L$(LIBUBOX_BUILD) -lubox -lblobmsg_json \
  -L$(UBUS_BUILD) -lubus

TARGET := hello_service
SRC := hello_service.c
OUT := $(OUTPUT_DIR)/$(TARGET)

all: $(OUT)

$(OUT): $(SRC)
	$(CC) -o $@ $^ $(CFLAGS) $(LDFLAGS)

clean:
	rm -f $(OUT)

