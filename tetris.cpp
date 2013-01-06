// Hari Ganesan 12/19/12
// Yale-Tetris

#include "SDL/SDL.h"
#include "SDL/SDL_opengl.h"
#include "SDL_ttf/SDL_ttf.h"
#include <iostream>
#include <sstream>
#include <string>
#include "Shape.h"

// window dimensions
const int WINDOW_WIDTH  = 600;
const int WINDOW_HEIGHT = 600;

using namespace std;

void runGame(); // runs the tetris game
bool checkEvents(SDL_Event event, Shape *s, Grid *g); // checks all events
void render(Grid *g, SDL_Surface *screen, SDL_Surface *text); // renders all graphics and audio to window

int main(int argc, char **argv) {
	// initialize SDL, TTF, and OpenGL
	SDL_Init(SDL_INIT_EVERYTHING);
	TTF_Init();

	SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_BUFFER_SIZE, 32);
	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 16);
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

	// initialize window properties
	SDL_WM_SetCaption("Tetris", NULL);
	SDL_SetVideoMode(WINDOW_WIDTH, WINDOW_HEIGHT, 32, SDL_OPENGL);
	glClearColor(0, 0, 0, 1); // RGBA
	glViewport(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT); // viewable part of the window
	glShadeModel(GL_SMOOTH); // add a gradient
	glMatrixMode(GL_PROJECTION); // 2D drawing
	glLoadIdentity(); // save state
	glDisable(GL_DEPTH_TEST); // disable 3D drawing

	runGame();

	TTF_Quit();
	SDL_Quit();
	return EXIT_SUCCESS;
}

void runGame() {
	cout << "game running" << endl;

	SDL_Surface *screen, *text;
	SDL_Color white = {220, 220, 220};
	TTF_Font *font = TTF_OpenFont("fonts/SignPaintersGothic.ttf", 32);
	text = TTF_RenderText_Solid(font, "0", white);

	bool isRunning = true; // if game is not yet over
	const int SPEED = 1; // speed of falling shape (1-5)
	int numShifts = 0; // number of shifts each turn
	int score = 0; // total score!
	// starting position of shape
	int SHAPE_X = GRID_WIDTH/2;
	int SHAPE_Y = GRID_HEIGHT - 4;

	SDL_Event event;
	Grid g = Grid();
	Shape s = Shape(SHAPE_X, SHAPE_Y);

	// main loop
	while (isRunning) {
		isRunning = checkEvents(event, &s, &g);

		// if there is a collision
		if (!s.moveDown(&g, SPEED)) {
			s.displayShape(&g);
			s.destroyShape(&g);

			// check for full rows
			if ((numShifts = g.checkShift()) > 0) {
				score += numShifts*numShifts*10;
			} else {
				score += 5;
			}

			// display score
			text = TTF_RenderText_Solid(font, (char *) score, white);

			// grab new shape
			s = Shape(SHAPE_X, SHAPE_Y);

			if (!s.displayShape(&g)) {// game is over!
				isRunning = false;
			}
		} else {
			s.displayShape(&g);
		}

		render(&g, screen, text);
		s.removeShape(&g);
	}

	SDL_FreeSurface(text);
	TTF_CloseFont(font);
}

//TODO: work with keydowns
bool checkEvents(SDL_Event event, Shape *s, Grid *g) {
	bool isRunning = true;

	while (SDL_PollEvent(&event)) {
		// window was closed or escape was pressed
		if (event.type == SDL_QUIT || 
			 (event.type == SDL_KEYUP && event.key.keysym.sym == SDLK_q)) {
			isRunning = false;
		// w turns screen white
		} else if (event.type == SDL_KEYUP && event.key.keysym.sym == SDLK_w) {
			glClearColor(1,1,1,1);
		// b turns screen black
		} else if (event.type == SDL_KEYUP && event.key.keysym.sym == SDLK_b) {
			glClearColor(0,0,0,1);
		// down moves shape down
		} else if (event.type == SDL_KEYUP && event.key.keysym.sym == SDLK_DOWN) {
			(*s).moveDown(g, MAX_SPEED);
		// up rotates CCW
		} else if (event.type == SDL_KEYUP && event.key.keysym.sym == SDLK_UP) {
			(*s).rotateShapeCCW();
		// move left
		} else if (event.type == SDL_KEYUP && event.key.keysym.sym == SDLK_LEFT) {
			(*s).moveLeft(g);
		// move right
		} else if (event.type == SDL_KEYUP && event.key.keysym.sym == SDLK_RIGHT) {
			(*s).moveRight(g);
		}
	}

	return isRunning;
}

// possible arguments for glBegin(): GL_POINTS, GL_LINES, GL_LINE_STRIP, 
// GL_LINE_LOOP, GL_QUADS, GL_TRIANGLES, GL_POLYGON
void render(Grid *g, SDL_Surface *screen, SDL_Surface *text) {
	glClear(GL_COLOR_BUFFER_BIT);
	glPushMatrix();
	// TODO: change to 0,1 for depth
	glOrtho(0, WINDOW_WIDTH, WINDOW_HEIGHT, 0, -1, 1); // set matrix

	////////////////
	// BEGIN DRAWING
	////////////////

	// GRID

	// gray color for grid
	glColor4ub(50, 50, 50, 255);

	// horizontal lines
	for (int i = 0; i <= GRID_HEIGHT; i++) {
		glBegin(GL_LINES);

		glVertex2f(150, (500-25*GRID_HEIGHT)+i*BLOCK_DIM);
		glVertex2f(150+GRID_WIDTH*BLOCK_DIM, (500-25*GRID_HEIGHT)+i*BLOCK_DIM);

		glEnd();
	}

	// vertical lines
	for (int i = 0; i <= GRID_WIDTH; i++) {
		glBegin(GL_LINES);

		glVertex2f(150+i*BLOCK_DIM, (500-25*GRID_HEIGHT));
		glVertex2f(150+i*BLOCK_DIM, (500-25*GRID_HEIGHT)+GRID_HEIGHT*BLOCK_DIM);

		glEnd();
	}

	// white color for blocks
	glColor4ub(220, 220, 220, 255);
	(*g).displayGrid(150, 500-25*GRID_HEIGHT);

	// TEXT

	SDL_BlitSurface(text, NULL, screen, NULL);

	///////////////
	// END DRAWING
	////////////////

	glPopMatrix();
	SDL_GL_SwapBuffers();
	SDL_Delay(33); // frame rate 30ms
}
