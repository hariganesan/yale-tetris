// Hari Ganesan 12/19/12
// Grid for yale-tetris

#include "Grid.h"

using namespace std;
//TODO: enum for EMPTY and FILLED

Grid::Grid() {
	currentSpeed = 1;
	currentHeight = 0;

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
	// check for errors
	if (grid[columnHeights[column]][column] != 0) {
		fprintf(stderr, "error: misplaced block\n");
		return;
	}

	// add block and increase column height and row stuffing
	grid[columnHeights[column]][column]++;
	columnHeights[column]++;
	rowStuffings[columnHeights[column] - 1]++;

	// update current height if needed
	if (columnHeights[column] > currentHeight)
		currentHeight = columnHeights[column];
}

void Grid::enterSingleBlock (int row, int column) {
	// check for errors
	if (grid[row][column] != 0) {
		fprintf(stderr, "error: misplaced block\n");
		return;
	}

	// add block and increase row stuffing and possibly column height
	grid[row][column]++;
	rowStuffings[row]++;
	if (row > columnHeights[column])
		columnHeights[column] = row+1;


	//TODO: check functionality
	// update current height if needed
	if (columnHeights[column] > currentHeight)
		currentHeight = columnHeights[column];
}

void Grid::enterFullBlock(int grid[][], int position) {
	;
}

void Grid::checkShift() {
	// a little inefficient, but not much: we could only check rows affected
	// by the block.
	for (int i = 0; i < GRID_HEIGHT; i++) {
		if (rowStuffings[i] >= GRID_WIDTH)
			shiftDown(i);
	}
}

void Grid::shiftDown(int row) {
	cout << row << endl;
	for (int i = row; i < (GRID_HEIGHT - 1); i++) {
		// move grid
		for (int j = 0; j < GRID_WIDTH; j++)
			grid[i][j] = grid[i+1][j];
		
		// shift all row stuffings
		rowStuffings[i] = rowStuffings[i+1];
	}

	// reset final row
	rowStuffings[GRID_HEIGHT - 1] = 0;
	for (int j = 0; j < GRID_WIDTH; j++)
		grid[GRID_HEIGHT - 1][j] = 0;

	// change column heights (-1)
	for (int j = 0; j < GRID_WIDTH; j++)
		columnHeights[j]--;

	// change current height
	currentHeight--;
}

void Grid::printGrid() {
	for (int i = GRID_HEIGHT - 1; i >= 0; i--) {
		cout << i << ": ";

		for (int j = 0; j < GRID_WIDTH; j++)
			cout << grid[i][j] << " ";

		cout << endl;
	}
}
