// Hari Ganesan 12/19/12
// Yale-Tetris

#include "SDL/SDL.h"
#include "SDL/SDL_opengl.h"
#include <iostream>
#include <sstream>
#include <string>
#include "Block.h"
#include "Grid.h"
//#include <OpenGL/gl.h>
//#include <OpenGL/glu.h>

#define WINDOW_WIDTH 600
#define WINDOW_HEIGHT 600


using namespace std;

bool checkEvents(SDL_Event event); // checks all events
void executeLogic(); // runs the tetris game
void render(); // renders all graphics and audio to window

int main(int argc, char **argv) {
	cout << "running program\n" << endl;

	// initialize SDL and OpenGL
	SDL_Init(SDL_INIT_EVERYTHING);

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

	SDL_Event event;
	cout << "OpenGL is running\n";
	bool isRunning = true; // if game is not yet over

	// main loop
	while (isRunning) {
		isRunning = checkEvents(event);

		//executeLogic();

		render();
	}
	//Block b = Block();

	//b.printBlock();

	//b.rotateBlockCW();
	//b.rotateBlockCCW();
	//printf("//////////////\n");
	//b.printBlock();

	SDL_Quit();
	return EXIT_SUCCESS;
}

bool checkEvents(SDL_Event event) {
	bool isRunning = true;

	while (SDL_PollEvent(&event)) {
		// window was closed or escape was pressed
		if (event.type == SDL_QUIT || 
			 (event.type == SDL_KEYUP && event.key.keysym.sym == SDLK_ESCAPE)) {
			isRunning = false;
		} else if (event.type == SDL_KEYUP && event.key.keysym.sym == SDLK_w) {
			glClearColor(1,1,1,1);
		} else if (event.type == SDL_KEYUP && event.key.keysym.sym == SDLK_b) {
			glClearColor(0,0,0,1);
		}
	}

	return isRunning;
}

void executeLogic() {
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

// possible arguments for glBegin(): GL_POINTS, GL_LINES, GL_LINE_STRIP, 
// GL_LINE_LOOP, GL_QUADS, GL_TRIANGLES, GL_POLYGON
void render() {
	glClear(GL_COLOR_BUFFER_BIT);
	glPushMatrix();
	// TODO: change to 0,1 for depth
	glOrtho(0, WINDOW_WIDTH, WINDOW_HEIGHT,0, -1, 1); // set matrix

	// BEGIN DRAWING

	glColor4ub(120,120,120,255);
	glBegin(GL_LINE_LOOP);

	glVertex2f(0,0);
	glVertex2f(50,0);
	glVertex2f(50,50);
	glVertex2f(0,50);

	glEnd();

	// END DRAWING

	glPopMatrix();
	SDL_GL_SwapBuffers();
	SDL_Delay(33); // frame rate 30ms
}
