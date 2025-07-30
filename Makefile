TOP_DIR := $(CURDIR)

.PHONY: all clean build-packages build-ubus-service

all: build-packages
# build-ubus-service

build-packages:
	$(MAKE) -C Packages

build-ubus-service:
	$(MAKE) -C Source PACKAGES_DIR=$(TOP_DIR)/Packages OUTPUT_DIR=$(TOP_DIR)

clean:
	$(MAKE) -C Packages clean
	$(MAKE) -C Source clean
	rm -f $(TOP_DIR)/hello_service

