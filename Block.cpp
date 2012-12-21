// Hari Ganesan 12/20/12
// Block use for yale-tetris

#include "Block.h"

using namespace std;

Block::Block() {
	// TODO: randomly select block from given choices
	// initialize block as 0s
	for (int i = 0; i < MAX_BLOCK_DIM; i++) {
		for (int j = 0; j < MAX_BLOCK_DIM; j++)
			grid[i][j] = 0;
	}

	for (int j = 0; j < MAX_BLOCK_DIM; j++) {
		grid[0][j] = 1;
	}
}

void Block::rotateBlockCW() {
	int newGrid[MAX_BLOCK_DIM][MAX_BLOCK_DIM];

	// push to new array
	for (int i = 0; i < MAX_BLOCK_DIM; i++) {
		for (int j = 0; j < MAX_BLOCK_DIM; j++)
			newGrid[MAX_BLOCK_DIM - j - 1][i] = grid[i][j];
	}

	// move back to original array
	for (int i = 0; i < MAX_BLOCK_DIM; i++) {
		for (int j = 0; j < MAX_BLOCK_DIM; j++)
			grid[i][j] = newGrid[i][j];
	}
}

void Block::rotateBlockCCW() {
	int newGrid[MAX_BLOCK_DIM][MAX_BLOCK_DIM];

	// push to new array
	for (int i = 0; i < MAX_BLOCK_DIM; i++) {
		for (int j = 0; j < MAX_BLOCK_DIM; j++)	
			newGrid[j][MAX_BLOCK_DIM - i - 1] = grid[i][j];
	}

	// push back to original array
	for (int i = 0; i < MAX_BLOCK_DIM; i++) {
		for (int j = 0; j < MAX_BLOCK_DIM; j++)
			grid[i][j] = newGrid[i][j];
	}
}

void Block::printBlock() {
	for (int i = MAX_BLOCK_DIM - 1; i >= 0; i--) {
		for (int j = 0; j < MAX_BLOCK_DIM; j++)
			cout << grid[i][j] << " ";

		cout << endl;
	}
}