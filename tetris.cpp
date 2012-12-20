// Hari Ganesan 12/19/12
// Yale-Tetris

#include <iostream>
#include <string>
#include "Grid.h"

const int GRID_HEIGHT = 10;
const int GRID_WIDTH = 10;

using std::cout;
using std::endl;

int main() {
	cout << "running program" << endl;

	Grid g = Grid(GRID_HEIGHT, GRID_WIDTH);

	g.fillGrid();
	g.printGrid();

	// main loop

	// while game is not over (height != 10)
		// grab and display next piece
		// allow input for position, rotation
		// update grid state
		// update grid display

	return EXIT_SUCCESS;
}
