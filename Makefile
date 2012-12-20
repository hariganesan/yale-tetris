# Hari Ganesan 12/19/12
# Makefile for yale-tetris

# compiler options
CC=g++
CFLAGS=

# build tetris and remove .o files
all: tetris clean

tetris: tetris.o
	$(CC) -o $@ $^

tetris.o: tetris.cpp
	$(CC) -c $(CFLAGS) $^

clean:
	rm *.o
