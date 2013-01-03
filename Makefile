# Hari Ganesan 12/19/12
# Makefile for yale-tetris

# compiler options
CC=g++
CFLAGS=-pedantic -Wall
SDL=-lSDL -lSDLmain
COCOA=-framework Cocoa
GL=-framework OpenGL

# build tetris and remove .o files
all: tetris clean

tetris: tetris.o Grid.o Block.o
	$(CC) -o $@ $(COCOA) $(GL) $(SDL) $^

tetris.o: tetris.cpp Grid.h Block.h
	$(CC) $(CFLAGS) -c $^

Grid.o: Grid.cpp Grid.h
	$(CC) $(CFLAGS) -c $^

Block.o: Block.cpp Block.h
	$(CC) $(CFLAGS) -c $^

clean:
	rm *.o
	rm *.h.gch
