// Hari Ganesan 12/20/12
// Shape use for yale-tetris

#include "Shape.h"

using namespace std;

Shape::Shape() {
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

void Shape::rotateShapeCCW() {
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
}

void Shape::printTextShape() {
	for (int i = SHAPE_DIM - 1; i >= 0; i--) {
		for (int j = 0; j < SHAPE_DIM; j++) {
			cout << grid[i][j] << " ";
		}

		cout << endl;
	}
}

void Shape::displayShape(Grid g, int x, int y) {
	;
}
