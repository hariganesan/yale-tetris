# Hari Ganesan 12/19/12
# Makefile for yale-tetris

# compiler options
CC=g++
CFLAGS=-pedantic -Wall
SDLFLAGS=-framework SDL -framework Cocoa
GLFLAGS=-framework OpenGL

# build tetris and remove .o files
all: tetris clean

tetris: tetris.o Grid.o Block.o
	$(CC) -o $@ $^

tetris.o: tetris.cpp SDLmain.m Grid.h Block.h
	$(CC) $(CFLAGS) $(SDLFLAGS) -c $^

Grid.o: Grid.cpp Grid.h
	$(CC) $(CFLAGS) -c $^

Block.o: Block.cpp Block.h
	$(CC) $(CFLAGS) -c $^

clean:
	rm *.o
	rm *.h.gch
