JSON_C_DIR := json-c
BUILD_DIR := $(JSON_C_DIR)/build

all: $(BUILD_DIR)/libjson-c.a

$(BUILD_DIR)/libjson-c.a:
	mkdir -p $(BUILD_DIR)
	cd $(BUILD_DIR) && cmake .. 
	cd $(BUILD_DIR) && make -j$$(nproc)

clean:
	rm -rf $(BUILD_DIR)

