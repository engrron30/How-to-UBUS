TOP_DIR   := $(CURDIR)
PKG_DIR   := $(TOP_DIR)/Packages
SRC_DIR   := $(TOP_DIR)/Source

.PHONY: all build-packages build-ubus-service clean


all: build-packages 
# build-ubus-service

build-packages:
	$(MAKE) -C $(PKG_DIR)

build-ubus-service:
	$(MAKE) -C $(SRC_DIR) \
		TOP_DIR=$(TOP_DIR) \
		PACKAGES_DIR=$(PKG_DIR) \
		OUTPUT_DIR=$(TOP_DIR)

clean:
	$(MAKE) -C Packages clean
	$(MAKE) -C Source clean

