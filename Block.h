// Hari Ganesan 12/20/12
// Block library file for yale-tetris

#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>

#define MAX_BLOCK_DIM 4

class Block {
private:
	int grid[MAX_BLOCK_DIM][MAX_BLOCK_DIM];
	int height;
	int width;
public:
	Block(); // default constructor; initializes block
	void rotateBlockCW(); // rotates block clockwise
	void rotateBlockCCW(); // rotates block counter-clockwise
	void printBlock(); // print the block to stdout
};