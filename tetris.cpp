// Hari Ganesan 12/19/12
// Yale-Tetris

#include <iostream>
#include <sstream>
#include <string>
#include "Block.h"
#include "Grid.h"

using namespace std;

int main() {
	cout << "running program\n" << endl;

	Grid g = Grid();

	g.printGrid();

	// main loop
	// while game is not over (height != 10)
	while (g.getCurrentHeight() != GRID_HEIGHT) {
		// grab and display next piece
		// allow input for position, rotation

		//check to see if input is a number
		//if not, then ask again
		stringstream ss;
		string input;
		int position;
		do {
			ss.str("");
			ss.clear();
			cout << "Enter a number:\n";
			cin >> input;
			ss << input;
			ss >> position;
		} while (ss.fail() || position > GRID_WIDTH || position < 1);

		// update grid state
		g.enterSingleBlock(position - 1);
		g.checkShift();
		// update grid display/display grid
		g.printGrid();
	}

	cout << "\nGame Over" << endl;

	return EXIT_SUCCESS;
}
