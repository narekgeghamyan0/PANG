CXX = g++
CXXFLAGS = -std=c++20 -Wall -Wextra -I./src
CXXSQL= -l sqlite3

SRC = \
    src/main.cpp \
    src/core/moment.cpp \
	src/core/lifemanager.cpp \
	src/core/user.cpp \
	src/core/maincontroller.cpp \
	src/db/dataBase.cpp

BIN_DIR = bin
TARGET = $(BIN_DIR)/pang

all: $(TARGET)

$(BIN_DIR):
	mkdir -p $(BIN_DIR)

$(TARGET): $(BIN_DIR) $(SRC)
	$(CXX) $(CXXFLAGS) $(SRC) -o $(TARGET) $(CXXSQL)

clean:
	rm -rf $(BIN_DIR)
