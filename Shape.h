// Hari Ganesan 12/20/12
// Shape library file for yale-tetris
// a Shape is a set of blocks.

#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
#include "Grid.h"

const int SHAPE_DIM = 4;
const int MAX_SPEED = 20;

class Shape {
private:
	// shape properties
	int grid[SHAPE_DIM][SHAPE_DIM];
	int height;
	int width;
	int x;
	int y;
	// used for falling shape
	int count;
public:
	Shape(int initX, int initY); // initializes shape (set of blocks)

	void rotateShapeCW(); // rotates Shape clockwise
	void rotateShapeCCW(Grid *g); // rotates Shape counter-clockwise
	void printTextShape(); // print the Shape to stdout
	bool displayShape(Grid *g); // print Shape to grid at x,y
	void removeShape(Grid *g); // remove Shape from grid at x, y
	void moveLeft(Grid *g); // move shape to the left
	void moveRight(Grid *g); // move shape to the right
	bool moveDown(Grid *g, const int SPEED); // move shape down given speed, false for collision
	void destroyShape(Grid *g); // displays and then destroys shape
};
