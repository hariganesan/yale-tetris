// Hari Ganesan 12/19/12
// Yale-Tetris

#include <iostream>
#include <string>
#include "Grid.h"



using std::cout;
using std::endl;

int main() {
	cout << "running program\n" << endl;

	Grid g = Grid();

	g.printGrid();

	// main loop

	// while game is not over (height != 10)
		// grab and display next piece
		// allow input for position, rotation
		// update grid state
		// update grid display

	return EXIT_SUCCESS;
}
