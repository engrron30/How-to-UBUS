PACKAGES_DIR ?= ../Packages
OUTPUT_DIR ?= ..

LIBUBOX_BUILD := $(PACKAGES_DIR)/libubox/build
UBUS_BUILD := $(PACKAGES_DIR)/ubus/build

CC := gcc
CFLAGS := -I$(PACKAGES_DIR)/libubox -I$(PACKAGES_DIR)/ubus
LDFLAGS := -L$(LIBUBOX_BUILD) -lubox -lblobmsg_json \
           -L$(UBUS_BUILD) -lubus

TARGET := hello_service
SRC := hello_service.c
OUT := $(OUTPUT_DIR)/$(TARGET)

all: $(OUT)

$(OUT): $(SRC)
	$(CC) -o $@ $^ $(CFLAGS) $(LDFLAGS)

clean:
	rm -f $(OUT)

