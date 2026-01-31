# ===========================
# Project Settings
# ===========================
progname := pang
CXX := g++
CXXFLAGS := -std=c++20 -Wall -Wextra -MMD -MP -I./src
CXXSQLFLAGS := -lsqlite3

SRC_DIR := src
TEST_SRC_DIR := tests
OBJ_DIR := build
BIN_DIR := bin

APP_TARGET := $(BIN_DIR)/$(progname)
TEST_TARGET := $(BIN_DIR)/pang_tests

# Detect macOS brew prefix
BREW_PREFIX := $(shell brew --prefix 2>/dev/null)
ifeq ($(BREW_PREFIX),)
    # Linux: do nothing
else
    # macOS: include brew headers
    CXXFLAGS += -I$(BREW_PREFIX)/include
endif

# ===========================
# Build Types
# ===========================
debug: CXXFLAGS += -g3
debug: app

release: CXXFLAGS += -O2 -DNDEBUG
release: app

# ===========================
# Source and Object Files
# ===========================
APP_MAIN := $(SRC_DIR)/main.cpp
APP_SOURCES := \
    $(wildcard $(SRC_DIR)/core/*.cpp) \
    $(wildcard $(SRC_DIR)/db/*.cpp) \
    $(wildcard $(SRC_DIR)/qt/*.cpp)
SOURCES := $(APP_MAIN) $(APP_SOURCES)
TEST_SOURCES := $(wildcard $(TEST_SRC_DIR)/*.cpp)

MAIN_OBJ := $(OBJ_DIR)/main.o
APP_OBJS := $(patsubst $(SRC_DIR)/%.cpp,$(OBJ_DIR)/%.o,$(APP_SOURCES))
OBJS := $(APP_OBJS) $(MAIN_OBJ)
TEST_OBJS := $(patsubst $(TEST_SRC_DIR)/%.cpp,$(OBJ_DIR)/tests/%.o,$(TEST_SOURCES))

# ===========================
# Pattern Rules
# ===========================
# Compile main source files

$(OBJ_DIR)/main.o: $(SRC_DIR)/main.cpp
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Compile test source files
$(OBJ_DIR)/tests/%.o: $(TEST_SRC_DIR)/%.cpp
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# ===========================
# Targets
# ===========================
app: $(APP_TARGET)
all: app test

$(BIN_DIR):
	@mkdir -p $(BIN_DIR)

$(APP_TARGET): $(OBJS) | $(BIN_DIR)
	$(CXX) $(CXXFLAGS) $^ -o $@ $(CXXSQLFLAGS)

$(TEST_TARGET): $(TEST_OBJS) $(APP_OBJS) | $(BIN_DIR)
	$(CXX) $(CXXFLAGS) $^ -o $@ $(CXXSQLFLAGS)

# ===========================
# Include auto-generated header dependencies
# ===========================
-include $(OBJS:.o=.d)
-include $(TEST_OBJS:.o=.d)

# ===========================
# Phony Targets
# ===========================
.PHONY: clean test

test: $(TEST_TARGET)
	./$(TEST_TARGET)

clean:
	rm -rf $(BIN_DIR) $(OBJ_DIR)