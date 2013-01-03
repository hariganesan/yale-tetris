// Hari Ganesan 12/19/12
// Yale-Tetris

//#include "SDL/SDLMain.h"
#include "SDL/SDL.h"
#include <iostream>
#include <sstream>
#include <string>
#include "Block.h"
#include "Grid.h"
//#include <OpenGL/gl.h>
//#include <OpenGL/glu.h>

using namespace std;

void runGame(); // runs the tetris game

int main(int argc, char **argv) {
	cout << "running program\n" << endl;


	SDL_Init(SDL_INIT_EVERYTHING);

	SDL_Quit();

	//Block b = Block();

	//b.printBlock();

	//b.rotateBlockCW();
	//b.rotateBlockCCW();
	//printf("//////////////\n");
	//b.printBlock();

	runGame();

	return EXIT_SUCCESS;
}

void runGame() {
	cout << "game initialized" << endl;
	Grid g = Grid();

	// main loop
	// while game is not over (height != 10)
	while (g.getCurrentHeight() != GRID_HEIGHT) {
		// grab and display next piece
		// allow input for position, rotation

		//check to see if input is a number
		//if not, then ask again
		stringstream ss;
		string input;
		int position, row;

		do {
			ss.str("");
			ss.clear();
			cout << "Enter row:\n";
			cin >> input;
			ss << input;
			ss >> row;
		} while (ss.fail() || row >= GRID_HEIGHT || row < 0);

		do {
			ss.str("");
			ss.clear();
			cout << "Enter column:\n";
			cin >> input;
			ss << input;
			ss >> position;
		} while (ss.fail() || position >= GRID_WIDTH || position < 0);

		g.enterSingleBlock(row, position);
		//g.enterSingleBlock(position);
		g.checkShift();
		// update grid display/display grid
		g.printGrid();
		//cout << g.getCurrentHeight() << endl;
	}

	cout << "\nGame Over" << endl;

	return;
}