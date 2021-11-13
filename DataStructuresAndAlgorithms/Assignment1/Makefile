.PHONY: clean tidy

CC=gcc
CFLAGS=-Wall -Werror -std=gnu99
LFLAGS=-lm
HDR=$(wildcard *.h)
SRC=$(filter-out $(wildcard *_test.c), $(wildcard *.c))
OBJ=$(SRC:.c=.o)

CFLAGS_TEST=$(CFLAGS) 
LFLAGS_TEST=$(LFLAGS) -lcheck -lm -lpthread -lrt -lsubunit
SRC_TEST=$(filter-out main.c, $(wildcard *.c))
OBJ_TEST=$(SRC_TEST:.c=.o)

main: $(OBJ)
	$(CC) $(CFLAGS) -o main $(OBJ) $(LFLAGS)

test: $(OBJ_TEST)
	$(CC) $(CFLAGS_TEST) -o test $(OBJ_TEST) $(LFLAGS_TEST)

%.o: %.c
	$(CC) -c $(CFLAGS) -o $@ $< $(LFLAGS)

%_test.o: %_test.c
	$(CC) -c $(CFLAGS_TEST) -o $@ $< $(LFLAGS_TEST)

clean:
	rm -rf *.o main test

tidy:
	rm -rf *.o
