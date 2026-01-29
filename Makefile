CXX = g++

BREW_PREFIX := $(shell brew --prefix 2>/dev/null)

CXXFLAGS = -std=c++20 -Wall -Wextra -I./src
ifeq ($(BREW_PREFIX),)
    # Linux case
else
    # macOS case
    CXXFLAGS += -I$(BREW_PREFIX)/include
endif

CXXSQL = -lsqlite3

SRC = \
    src/main.cpp \
    src/core/moment.cpp \
    src/core/lifemanager.cpp \
    src/core/user.cpp \
    src/core/maincontroller.cpp \
    src/db/dataBase.cpp

DB_SRC = \
    src/db/dataBase.cpp

CORE_SRC = \
    src/core/moment.cpp \
    src/core/lifemanager.cpp \
    src/core/user.cpp

TEST_SRC = \
    tests/test_moment.cpp \
    tests/test_user.cpp \
    tests/test_lifemanager.cpp \
    tests/test_db.cpp

BIN_DIR = bin
APP_TARGET = $(BIN_DIR)/pang
TEST_TARGET = $(BIN_DIR)/tests

.PHONY: all app tests test clean

all: app

$(BIN_DIR):
	mkdir -p $(BIN_DIR)

app: $(BIN_DIR)
	$(CXX) $(CXXFLAGS) $(SRC) -o $(APP_TARGET) $(CXXSQL)

tests: $(BIN_DIR)
	$(CXX) $(CXXFLAGS) $(CORE_SRC) $(DB_SRC) $(TEST_SRC) \
	    -o $(TEST_TARGET) $(CXXSQL)

test: tests
	./$(TEST_TARGET)

clean:
	rm -rf $(BIN_DIR)
