// Hari Ganesan 12/20/12
// Shape library file for yale-tetris
// a Shape is a set of blocks.

#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
#include "Grid.h"

const int SHAPE_DIM = 4;

class Shape {
private:
	int grid[SHAPE_DIM][SHAPE_DIM];
	int height;
	int width;
public:
	Shape(); // default constructor; initializes shape (set of blocks)
	void rotateShapeCW(); // rotates Shape clockwise
	void rotateShapeCCW(); // rotates Shape counter-clockwise
	void printTextShape(); // print the Shape to stdout
	void displayShape(Grid g, int x, int y); // print Shape to grid at x,y
};
