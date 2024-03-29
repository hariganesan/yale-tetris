// Hari Ganesan 12/19/12
// Grid for yale-tetris

#include "Grid.h"

using namespace std;
//TODO: enum for EMPTY and FILLED

Grid::Grid() {
	currentSpeed = 1;
	currentHeight = 0;

	// initialize grid
	clearGrid();

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

bool Grid::blockExists(int column, int row) {
	return (grid[row][column] == 1) ? true : false;
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

bool Grid::enterSingleBlock (int column, int row) {
	// check for errors
	if (grid[row][column] != 0) {
		fprintf(stderr, "error: misplaced block at %d, %d\n", column, row);
		return false;
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

	return true;
}

void Grid::removeSingleBlock(int column, int row) {
	if (grid[row][column] != 1) {
		fprintf(stderr, "error: cannot remove block at %d, %d\n", column, row);
		return;
	}

	grid[row][column]--;
	rowStuffings[row]--;
	// TODO: columnheights, currentheight

}

int Grid::checkShift() {
	int count = 0;
	// a little inefficient, but not much: we could only check rows affected
	// by the block.
	for (int i = 0; i < GRID_HEIGHT; i++) {
		if (rowStuffings[i] >= GRID_WIDTH) {
			shiftDown(i);
			i -= 1;
			count++;
		}
	}

	return count;
}

void Grid::shiftDown(int row) {
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

void Grid::printTextGrid() {
	for (int i = GRID_HEIGHT - 1; i >= 0; i--) {
		cout << i << ": ";

		for (int j = 0; j < GRID_WIDTH; j++)
			cout << grid[i][j] << " ";

		cout << endl;
	}
}

void Grid::displayGrid(int x, int y) {
	for (int i = 0; i < GRID_HEIGHT; i++) {
		for (int j = 0; j < GRID_WIDTH; j++) {
			if (grid[i][j] == 1) {
				glBegin(GL_QUADS);

				// we need to flip the vertical axis
				glVertex2f(x+j*BLOCK_DIM, y+BLOCK_DIM*GRID_HEIGHT-i*BLOCK_DIM);
				glVertex2f(x+(j+1)*BLOCK_DIM, y+BLOCK_DIM*GRID_HEIGHT-i*BLOCK_DIM);
				glVertex2f(x+(j+1)*BLOCK_DIM, y+BLOCK_DIM*GRID_HEIGHT-(i+1)*BLOCK_DIM);
				glVertex2f(x+j*BLOCK_DIM, y+BLOCK_DIM*GRID_HEIGHT-(i+1)*BLOCK_DIM);

				glEnd();
			}
		}
	}
}

void Grid::clearGrid() {
	for (int i = 0; i < GRID_HEIGHT; i++) {
		for (int j = 0; j < GRID_WIDTH; j++) {
			grid[i][j] = 0;
		}
	}
}