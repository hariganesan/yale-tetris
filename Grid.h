//Hari Ganesan 12/19/12
// Grid library file for yale-tetris

#include "SDL/SDL.h"
#include "SDL/SDL_opengl.h"
#include <iostream>
#include <string>

const int GRID_HEIGHT = 15;
const int GRID_WIDTH = 10;

const int BLOCK_DIM = 25; // single block width and height

class Grid {
private:
	int grid[GRID_HEIGHT][GRID_WIDTH];
	int columnHeights[GRID_WIDTH]; // how high each column is
	int rowStuffings[GRID_HEIGHT]; // how many filled in each row
	int currentHeight; // height of highest filled box
	int currentSpeed; // current speed
public:
	Grid(); // default constructor; initializes grid

	int getCurrentHeight();
	bool blockExists(int column, int row); // checks to see if block is at (r, c)
	void enterSingleBlock(int column); // enter block given column
	bool enterSingleBlock(int column, int row); // enter block given row & column
	void removeSingleBlock(int column, int row);
	int checkShift(); // check to see which (if any) shifts need to be made
	void shiftDown(int row); // shift down one based on row
	void printTextGrid(); // print out grid to stdout
	void displayGrid(int x, int y); // print grid to opengl
	void clearGrid(); // clear grid to all 0s
};
