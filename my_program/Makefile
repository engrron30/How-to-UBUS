# Paths
LIBUBOX_DIR := ../libubox
UBUS_DIR := ../ubus

LIBUBOX_BUILD := $(LIBUBOX_DIR)/build
UBUS_BUILD := $(UBUS_DIR)/build

# Compiler and flags
CC := gcc
CFLAGS := -I$(LIBUBOX_DIR) -I$(UBUS_DIR)
LDFLAGS := -L$(LIBUBOX_BUILD) -lubox -lblobmsg_json \
           -L$(UBUS_BUILD) -lubus

# Target
TARGET := hello_service
SRC := hello_service.c

all: $(TARGET)

$(TARGET): $(SRC)
	$(CC) -o $@ $^ $(CFLAGS) $(LDFLAGS)

clean:
	rm -f $(TARGET)

