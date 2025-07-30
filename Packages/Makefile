PKG_DIR := $(CURDIR)

# JSON-C
JSON_C_DIR := json-c
JSON_BUILD_DIR := $(JSON_C_DIR)/build
JSON_STATIC_LIB := $(JSON_BUILD_DIR)/libjson-c.a

# libubox
UBOX_DIR := libubox
UBOX_BUILD_DIR := $(UBOX_DIR)/build
UBOX_STATIC_LIB := $(UBOX_BUILD_DIR)/libubox.a

UBUS_DIR := ubus
UBUS_BUILD_DIR := $(UBUS_DIR)/build
UBUS_STATIC_LIB := $(UBUS_BUILD_DIR)/libubus.a


# All target
all: $(JSON_STATIC_LIB) $(UBOX_STATIC_LIB) $(UBUS_STATIC_LIB)

# Build JSON-C
$(JSON_STATIC_LIB): $(JSON_C_DIR)
	mkdir -p $(JSON_BUILD_DIR)
	cd $(JSON_BUILD_DIR) && cmake .. -DCMAKE_POSITION_INDEPENDENT_CODE=ON
	cd $(JSON_BUILD_DIR) && make -j$$(nproc)

# Build libubox without Lua
$(UBOX_STATIC_LIB): $(UBOX_DIR)
	mkdir -p $(UBOX_BUILD_DIR)
	cd $(UBOX_BUILD_DIR) && cmake .. -DCMAKE_POSITION_INDEPENDENT_CODE=ON -DBUILD_LUA=OFF
	cd $(UBOX_BUILD_DIR) && make -j$$(nproc)

$(UBUS_STATIC_LIB): $(LIBUBOX_STATIC_LIB)
	mkdir -p $(UBUS_BUILD_DIR)
	cd $(UBUS_BUILD_DIR) && cmake .. \
		-DCMAKE_POSITION_INDEPENDENT_CODE=ON \
		-DBUILD_LUA=OFF \
		-Dubox_include_dir=$(PKG_DIR)/libubox \
		-Dubox_library=$(PKG_DIR)/libubox/build/libubox.a \
		-Dblob_library=$(PKG_DIR)/libubox/build/libblobmsg_json.a \
		-DCMAKE_INCLUDE_PATH=$(PKG_DIR)/libubox \
        -DCMAKE_C_FLAGS="-I$(abspath $(PKG_DIR))" \
        -DCMAKE_EXE_LINKER_FLAGS="-lrt" \
        -DCMAKE_PREFIX_PATH=$(PKG_DIR)/libubox/build
	cd $(UBUS_BUILD_DIR) && make -j$$(nproc)

clean:
	rm -rf $(JSON_BUILD_DIR) $(UBOX_BUILD_DIR) $(UBUS_BUILD_DIR)

