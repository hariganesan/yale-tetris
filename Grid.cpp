// Hari Ganesan 12/19/12
// Grid for yale-tetris

#include "Grid.h"

using namespace std;

Grid::Grid() {
	currentSpeed = 1;
	currentHeight = 0;

	// TODO: change to inputs
	//int newGrid[10][10];
	//this.grid = newGrid;

	// initialize grid
	for (int i = 0; i < GRID_HEIGHT; i++) {
		for (int j = 0; j < GRID_WIDTH; j++) {
			grid[i][j] = 0;
		}
	}

	// initialize row stuffings
	for (int i = 0; i < GRID_HEIGHT; i++) {
		rowStuffings[i] = 0;
	}

	// initialize column heights
	for (int j = 0; j < GRID_WIDTH; j++) {
		columnHeights[j] = 0;
	}
}

int Grid::getCurrentHeight() {
	return currentHeight;
}

void Grid::enterSingleBlock(int column) {
	if (grid[columnHeights[column] + 1][column] != 0)
		fprintf(stderr, "error: misplaced block\n");
}

void Grid::printGrid() {
	for (int i = 0; i < GRID_HEIGHT; i++) {
		for (int j = 0; j < GRID_WIDTH; j++) {
			cout << grid[i][j] << " ";
		}

		cout << endl;
	}
}
