# Hari Ganesan 12/19/12
# Makefile for yale-tetris

# compiler options
CC=g++
CFLAGS=-pedantic -Wall -I/sw/include -L/sw/lib
SDL=-lSDLmain -lSDL -lSDL_ttf -lSDL_mixer
COCOA=-framework Cocoa
GL=-framework OpenGL -L/sw/lib

# build tetris and remove .o files
all: tetris clean

tetris: tetris.o Grid.o Shape.o
	$(CC) -o $@ $(COCOA) $(GL) $(SDL) $^

tetris.o: tetris.cpp Shape.h
	$(CC) $(CFLAGS) -c $^

Grid.o: Grid.cpp Grid.h
	$(CC) $(CFLAGS) -c $^

Shape.o: Shape.cpp Shape.h Grid.h
	$(CC) $(CFLAGS) -c $^

clean:
	rm *.o
	rm *.h.gch
