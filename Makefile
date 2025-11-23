CC = gcc
CFLAGS = -Wall -Wextra -std=c99 -I/usr/local/include -Isrc
LDFLAGS = -L/usr/local/lib -lraylib -llua -lm -ldl -lpthread

SRC_DIR = src
OBJ_DIR = obj
BIN_DIR = bin

SOURCES = $(wildcard $(SRC_DIR)/*.c)
OBJECTS = $(SOURCES:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)
TARGET = $(BIN_DIR)/headclicker

.PHONY: all clean

all: $(TARGET)

$(TARGET): $(OBJECTS) | $(BIN_DIR)
$(CC) $(OBJECTS) -o $@ $(LDFLAGS)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
$(CC) $(CFLAGS) -c $< -o $@

$(BIN_DIR):
mkdir -p $(BIN_DIR)

$(OBJ_DIR):
mkdir -p $(OBJ_DIR)

clean:
rm -rf $(OBJ_DIR) $(BIN_DIR)

run: $(TARGET)
./$(TARGET)
