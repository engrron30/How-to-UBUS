# JSON Library
JSON_C_DIR := json-c
JSON_BUILD_DIR := $(JSON_C_DIR)/build

# Static Libraries
STATIC_LIB := $(BUILD_DIR)/libjson-c.a

all: $(STATIC_LIB)

$(STATIC_LIB): $(JSON_C_DIR)
	mkdir -p $(JSON_BUILD_DIR)
	cd $(JSON_BUILD_DIR) && cmake .. -DCMAKE_POSITION_INDEPENDENT_CODE=ON
	cd $(JSON_BUILD_DIR) && make -j$$(nproc)

clean:
	rm -rf $(JSON_BUILD_DIR)

