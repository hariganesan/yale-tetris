# Hari Ganesan 12/19/12
# Makefile for yale-tetris

# compiler options
CC=g++
CFLAGS=-pedantic -Wall

# build tetris and remove .o files
all: tetris clean

tetris: tetris.o Grid.o
	$(CC) -o $@ $^

tetris.o: tetris.cpp Grid.h
	$(CC) $(CFLAGS) -c $^

Grid.o: Grid.cpp Grid.h
	$(CC) $(CFLAGS) -c $^

move:
	cd src/

clean:
	rm *.o
	rm *.h.gch
