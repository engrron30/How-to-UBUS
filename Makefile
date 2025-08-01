TOP_DIR   := $(CURDIR)
PKG_DIR   := $(TOP_DIR)/Packages
SRC_DIR   := $(TOP_DIR)/Source
SCR_DIR   := $(TOP_DIR)/Scripts

UBUSD_BIN := ubusd
HELLO_SRV_BIN := hello_service

.PHONY: all build-packages build-ubus-service clean


all: build-packages build-ubus-service

build-packages:
	$(MAKE) -C $(PKG_DIR)

build-ubus-service:
	$(MAKE) -C $(SRC_DIR) 			\
		TOP_DIR=$(TOP_DIR) 		\
		PKG_DIR=$(PKG_DIR) 		\
		OUTPUT_DIR=$(SCR_DIR)

clean:
	$(MAKE) -C Packages clean
	$(MAKE) -C Source clean
	rm -f $(SCR_DIR)/$(UBUSD_BIN)		\
	      $(SCR_DIR)/$(HELLO_SRV_BIN)	\
	      $(SCR_DIR)/*.sock

