CXX = g++
CXXFLAGS = -std=c++20 -Wall -Wextra -I./src

SRC = \
    src/main.cpp \
    src/core/moment.cpp

BIN_DIR = bin
TARGET = $(BIN_DIR)/pang

all: $(TARGET)

$(BIN_DIR):
	mkdir -p $(BIN_DIR)

$(TARGET): $(BIN_DIR) $(SRC)
	$(CXX) $(CXXFLAGS) $(SRC) -o $(TARGET)

clean:
	rm -rf $(BIN_DIR)
