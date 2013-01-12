// Hari Ganesan 12/20/12
// Shape use for yale-tetris

#include "Shape.h"

using namespace std;

Shape::Shape(int initX, int initY) {
	// set x and y
	x = initX;
	y = initY;

	//reset timer
	count = 0;

	// initialize Shape as 0s
	for (int i = 0; i < SHAPE_DIM; i++) {
		for (int j = 0; j < SHAPE_DIM; j++) {
			grid[i][j] = 0;
		}
	}

	// NOTE: based on 4x4 Shape
	// randomly select the Shape
	int randomNumber = (int) time(NULL);
	switch (randomNumber % 7) {
		// L Shapes
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
		// S Shapes
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
		// I Shape
		case 4:
			grid[0][1] = 1;
			grid[0][2] = 1;
			grid[0][0] = 1;
			grid[0][3] = 1;
			break;
		// O Shape
		case 5:
			grid[0][0] = 1;
			grid[0][1] = 1;
			grid[1][0] = 1;
			grid[1][1] = 1;
			break;
		// T Shape
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

//TODO: check right edge
void Shape::rotateShapeCW() {
	int newGrid[SHAPE_DIM][SHAPE_DIM];

	// push to new array
	for (int i = 0; i < SHAPE_DIM; i++) {
		for (int j = 0; j < SHAPE_DIM; j++) {
			newGrid[SHAPE_DIM - j - 1][i] = grid[i][j];
		}
	}

	// push down
	while (newGrid[0][0] != 1 && newGrid[0][1] != 1 && newGrid[0][2] != 1) {
		for (int i = 0; i < SHAPE_DIM - 1; i++) {
			for (int j = 0; j < SHAPE_DIM; j++) {
				newGrid[i][j] = newGrid[i+1][j];
			}
		}

		for (int j = 0; j < SHAPE_DIM; j++) {
			newGrid[SHAPE_DIM - 1][j] = 0;
		}
	}

	// move back to original array
	for (int i = 0; i < SHAPE_DIM; i++) {
		for (int j = 0; j < SHAPE_DIM; j++) {
			grid[i][j] = newGrid[i][j];
		}
	}
}

//TODO: check right edge
void Shape::rotateShapeCCW(Grid *g) {
	int newGrid[SHAPE_DIM][SHAPE_DIM];

	// push to new array
	for (int i = 0; i < SHAPE_DIM; i++) {
		for (int j = 0; j < SHAPE_DIM; j++)	{
			newGrid[j][SHAPE_DIM - i - 1] = grid[i][j];
		}
	}

	// push left
	while (newGrid[0][0] != 1 && newGrid[1][0] != 1 && newGrid[2][0] != 1) {
		for (int i = 0; i < SHAPE_DIM; i++) {
			for (int j = 0; j < SHAPE_DIM - 1; j++) {
				newGrid[i][j] = newGrid[i][j+1];
			}
		}

		for (int i = 0; i < SHAPE_DIM; i++) {
			newGrid[i][SHAPE_DIM - 1] = 0;
		}
	}

	// push back to original array
	for (int i = 0; i < SHAPE_DIM; i++) {
		for (int j = 0; j < SHAPE_DIM; j++) {
			grid[i][j] = newGrid[i][j];
		}
	}
	
	// check right edge of grid
	const int oldX = x;
	for (int i = SHAPE_DIM - 1; oldX + i >= GRID_WIDTH; i--) {
		for (int j = 0; j < SHAPE_DIM; j++) {
			if (newGrid[i][j] == 1) {
				x -= 1;
				break;
			}
		}
	}
}

void Shape::printTextShape() {
	for (int i = SHAPE_DIM - 1; i >= 0; i--) {
		for (int j = 0; j < SHAPE_DIM; j++) {
			cout << grid[i][j] << " ";
		}

		cout << endl;
	}
}

bool Shape::displayShape(Grid *g) {
	for (int i = 0; i < SHAPE_DIM; i++) {
		for (int j = 0; j < SHAPE_DIM; j++) {	
			if (grid[i][j] == 1 && !(*g).enterSingleBlock(x+i, y+j)) {
				return false;
			}
		}
	}

	return true;
}

void Shape::removeShape(Grid *g) {
	for (int i = 0; i < SHAPE_DIM; i++) {
		for (int j = 0; j < SHAPE_DIM; j++) {	
			if (grid[i][j] == 1) {
				(*g).removeSingleBlock(x+i, y+j);
			}
		}
	}
}

// we need to check against a) edges and b) collisions
void Shape::moveLeft(Grid *g) {
	bool collision = false;

	// move over and check new (1)s on grid
	for (int i = 0; i < SHAPE_DIM; i++) {
		for (int j = 0; j < SHAPE_DIM; j++) {
			if (grid[i][j] == 1) {
				// check edge/collision
				if (x+i-1 < 0 || (*g).blockExists(x+i-1, y+j)) {
					collision = true;
				}
			}
		}
	}	

	// update x-y
	if (!collision) {
		x -= 1;
	}
}

void Shape::moveRight(Grid *g) {
	bool collision = false;

	// move over and check new (1)s on grid
	for (int i = 0; i < SHAPE_DIM; i++) {
		for (int j = 0; j < SHAPE_DIM; j++) {
			if (grid[i][j] == 1) {
				// check edge/collision
				if (x+i+1 >= GRID_WIDTH || (*g).blockExists(x+i+1, y+j)) {
					collision = true;
				}
			}
		}
	}	

	// update x-y
	if (!collision) {
		x += 1;
	}
}

bool Shape::moveDown(Grid *g, const int SPEED) {
	bool collision = false;
	count += SPEED;

	// if time, then move down
	if (count > MAX_SPEED) {
		count = 0;

		// move down and check new (1)s on grid
		for (int i = 0; i < SHAPE_DIM; i++) {
			for (int j = 0; j < SHAPE_DIM; j++) {
				if (grid[i][j] == 1) {
					// check edge/collision
					if (y+j-1 < 0 || (*g).blockExists(x+i, y+j-1)) {
						collision = true;
					}
				}
			}
		}	

		// update x-y
		if (!collision) {
			y -= 1;
		}
	}

	return !collision;
}

void Shape::destroyShape(Grid *g) {
	// no need to destroy if shape was allocated statically
	;
}
