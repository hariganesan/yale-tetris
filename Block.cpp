// Hari Ganesan 12/20/12
// Block use for yale-tetris

#include "Block.h"

using namespace std;

Block::Block() {
	// initialize block as 0s
	for (int i = 0; i < MAX_BLOCK_DIM; i++) {
		for (int j = 0; j < MAX_BLOCK_DIM; j++) {
			grid[i][j] = 0;
		}
	}

	// NOTE: based on 4x4 block
	// randomly select the block
	int randomNumber = (int) time(NULL);
	switch (randomNumber % 7) {
		// L blocks
		case 0:
			grid[0][1] = 1;
			grid[0][2] = 1;
			grid[0][0] = 1;
			grid[1][0] = 1;
			break;
		case 1:
			grid[0][0] = 1;
			grid[0][1] = 1;
			grid[0][2] = 1;
			grid[1][2] = 1;
			break;
		// S blocks
		case 2:
			grid[0][1] = 1;
			grid[0][2] = 1;
			grid[1][0] = 1;
			grid[1][1] = 1;
			break;
		case 3:
			grid[0][0] = 1;
			grid[0][1] = 1;
			grid[1][1] = 1;
			grid[1][2] = 1;
			break;
		// I block
		case 4:
			grid[0][1] = 1;
			grid[0][2] = 1;
			grid[0][0] = 1;
			grid[0][3] = 1;
			break;
		// O block
		case 5:
			grid[0][0] = 1;
			grid[0][1] = 1;
			grid[1][0] = 1;
			grid[1][1] = 1;
			break;
		// T block
		case 6:
			grid[0][1] = 1;
			grid[0][2] = 1;
			grid[0][0] = 1;
			grid[1][1] = 1;
			break;
		default:
			fprintf(stderr, "error: rand()");
	}
}

void Block::rotateBlockCW() {
	int newGrid[MAX_BLOCK_DIM][MAX_BLOCK_DIM];

	// push to new array
	for (int i = 0; i < MAX_BLOCK_DIM; i++) {
		for (int j = 0; j < MAX_BLOCK_DIM; j++) {
			newGrid[MAX_BLOCK_DIM - j - 1][i] = grid[i][j];
		}
	}

	// push down
	while (newGrid[0][0] != 1 && newGrid[0][1] != 1 && newGrid[0][2] != 1) {
		for (int i = 0; i < MAX_BLOCK_DIM - 1; i++) {
			for (int j = 0; j < MAX_BLOCK_DIM; j++) {
				newGrid[i][j] = newGrid[i+1][j];
			}
		}

		for (int j = 0; j < MAX_BLOCK_DIM; j++) {
			newGrid[MAX_BLOCK_DIM - 1][j] = 0;
		}
	}

	// move back to original array
	for (int i = 0; i < MAX_BLOCK_DIM; i++) {
		for (int j = 0; j < MAX_BLOCK_DIM; j++) {
			grid[i][j] = newGrid[i][j];
		}
	}
}

void Block::rotateBlockCCW() {
	int newGrid[MAX_BLOCK_DIM][MAX_BLOCK_DIM];

	// push to new array
	for (int i = 0; i < MAX_BLOCK_DIM; i++) {
		for (int j = 0; j < MAX_BLOCK_DIM; j++)	{
			newGrid[j][MAX_BLOCK_DIM - i - 1] = grid[i][j];
		}
	}

	// push left
	while (newGrid[0][0] != 1 && newGrid[1][0] != 1 && newGrid[2][0] != 1) {
		for (int i = 0; i < MAX_BLOCK_DIM; i++) {
			for (int j = 0; j < MAX_BLOCK_DIM - 1; j++) {
				newGrid[i][j] = newGrid[i][j+1];
			}
		}

		for (int i = 0; i < MAX_BLOCK_DIM; i++) {
			newGrid[i][MAX_BLOCK_DIM - 1] = 0;
		}
	}

	// push back to original array
	for (int i = 0; i < MAX_BLOCK_DIM; i++) {
		for (int j = 0; j < MAX_BLOCK_DIM; j++) {
			grid[i][j] = newGrid[i][j];
		}
	}
}

void Block::printBlock() {
	for (int i = MAX_BLOCK_DIM - 1; i >= 0; i--) {
		for (int j = 0; j < MAX_BLOCK_DIM; j++) {
			cout << grid[i][j] << " ";
		}

		cout << endl;
	}
}