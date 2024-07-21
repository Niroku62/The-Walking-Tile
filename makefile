CC = gcc
CCFLAGS = -I ./include
BIN = ./bin/test.exe
SOURCES = $(wildcard ./src/*.c)
OBJECTS = $(patsubst ./src/%.c,./obj/%.o,$(SOURCES))

.PHONY: run

run: $(BIN)
	$<

$(BIN): $(OBJECTS)
	$(CC) $^ -o $(BIN)

./obj/%.o: ./src/%.c
	$(CC) $(CCFLAGS) -c $^ -o $@
