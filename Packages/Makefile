JSON_C_DIR := json-c
BUILD_DIR := $(JSON_C_DIR)/build
STATIC_LIB := $(BUILD_DIR)/libjson-c.a

all: $(STATIC_LIB)

$(STATIC_LIB): $(JSON_C_DIR)
	mkdir -p $(BUILD_DIR)
	cd $(BUILD_DIR) && cmake .. -DCMAKE_POSITION_INDEPENDENT_CODE=ON
	cd $(BUILD_DIR) && make -j$$(nproc)

clean:
	rm -rf $(BUILD_DIR)

