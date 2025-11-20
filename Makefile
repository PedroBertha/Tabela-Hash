CC = gcc
CFLAGS = -Wall -Wextra -std=c11 -O2

SRC = src/hashtable.c src/dlist.c src/sort_utils.c src/utils.c src/main.c
OBJ = $(SRC:.c=.o)
TARGET = build/hash_app

all: $(TARGET)

$(TARGET): $(OBJ)
	@mkdir -p build out
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJ)

src/%.o: src/%.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf build/*.o $(TARGET) out/*

.PHONY: all clean
