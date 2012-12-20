//Hari Ganesan 12/19/12
// Grid library file for yale-tetris

#include <iostream>
#include <string>

const int GRID_HEIGHT = 10;
const int GRID_WIDTH = 10;

class Grid {
	private:
		int grid[GRID_HEIGHT][GRID_WIDTH]; // grid pointer
		int columnHeights[GRID_WIDTH]; // how high each column is
		int rowStuffings[GRID_HEIGHT]; // how many filled in each row
		int currentHeight; // height of highest filled box
		int currentSpeed; // current speed
	public:
		Grid(); // default constructor

		int getCurrentHeight();
		void enterSingleBlock(int column); // enter block given column
		void checkShift(); // check to see which (if any) shifts need to be made
		void shiftDown(int row); // shift down one based on row
		void printGrid(); // print out entire grid
};
