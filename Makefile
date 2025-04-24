CC = gcc
CFLAGS = -Wall -Wextra -O2
LDFLAGS = -lm

SRC_DIR = src
BIN_DIR = bin

TARGET = $(BIN_DIR)/cpu_monitor

.PHONY: all clean

all: $(TARGET)

$(TARGET): $(SRC_DIR)/cpu_monitor.c
	@mkdir -p $(BIN_DIR)
	$(CC) $(CFLAGS) $< -o $@ $(LDFLAGS)

clean:
	rm -rf $(BIN_DIR)
