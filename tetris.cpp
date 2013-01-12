// Hari Ganesan 12/19/12
// Yale-Tetris

#include "SDL/SDL.h"
#include "SDL/SDL_opengl.h"
#include "SDL_ttf/SDL_ttf.h"
//#include "FTGL/ftgl.h"
//#include "OpenGL/gl.h"
//#include "OpenGL/glu.h"
//#include "OpenGL/freeglut.h"
//#include "GL/freeglut.h"
#include <iostream>
#include <sstream>
#include <string>
#include <math.h>
#include "Shape.h"

// window dimensions
const int WINDOW_WIDTH  = 600;
const int WINDOW_HEIGHT = 600;
const int GRID_X = 175;

// font
const char *fontpath = "fonts/chintzy.ttf";

using namespace std;

void runGame(); // runs the tetris game
bool checkEvents(SDL_Event event, Shape *s, Grid *g, bool *isPaused); // checks all events
void render(Grid *g, int score, TTF_Font *font, SDL_Color fontColor); // renders all graphics and audio to window
void SDL_GL_RenderText(const char *text, TTF_Font *font, SDL_Color color, SDL_Rect *location);

int main(int argc, char **argv) {
	// initialize SDL, TTF, and OpenGL
	SDL_Init(SDL_INIT_EVERYTHING);
	//glutInit(&argc, argv);
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

	//FTFont *font = new FTGLTextureFont(fontpath);
	TTF_Font *font = TTF_OpenFont(fontpath, 48);
	SDL_Color fontColor = {200, 200, 200};
	//SDL_Surface *text, *screen;
	//font->FaceSize(32);
	bool isRunning = true; // if game is not yet over
	bool isPaused = false; // game is paused
	const int SPEED = 1; // speed of falling shape (1-5)
	int numShifts = 0; // number of shifts each turn
	int score = 0; // total score!
	int timeElapsed = 0;
	// starting position of shape
	int SHAPE_X = GRID_WIDTH/2;
	int SHAPE_Y = GRID_HEIGHT - 4;

	SDL_Event event;
	Grid g = Grid();
	Shape s = Shape(SHAPE_X, SHAPE_Y);

	// main loop
	while (isRunning) {
		isRunning = checkEvents(event, &s, &g, &isPaused);

		// if there is a collision
		if (!isPaused && !s.moveDown(&g, SPEED)) {
			s.displayShape(&g);
			s.destroyShape(&g);

			// check for full rows
			if ((numShifts = g.checkShift()) > 0) {
				score += numShifts*numShifts*100;
			} else {
				score += 50;
			}

			score += SPEED*100-timeElapsed/5;
			timeElapsed = 0;

			// grab new shape
			s = Shape(SHAPE_X, SHAPE_Y);

			// game is over!
			if (!s.displayShape(&g)) {
				isRunning = false;
			}
		} else if (isPaused) {
			s.displayShape(&g);
		} else {
			s.displayShape(&g);
			timeElapsed++;
		}

		render(&g, score, font, fontColor);
		s.removeShape(&g);
	}

	//SDL_FreeSurface(text);
	//SDL_FreeSurface(screen);
	TTF_CloseFont(font);
}

//TODO: work with keydowns
bool checkEvents(SDL_Event event, Shape *s, Grid *g, bool *isPaused) {
	bool isRunning = true;

	while (SDL_PollEvent(&event)) {
		// window was closed or escape was pressed
		if (event.type == SDL_QUIT || 
			 (event.type == SDL_KEYUP && event.key.keysym.sym == SDLK_q)) {
			isRunning = false;
		// pause the game
		} else if (event.type == SDL_KEYUP && event.key.keysym.sym == SDLK_p) {
			(*isPaused) = !(*isPaused);
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
			(*s).rotateShapeCCW(g);
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
void render(Grid *g, int score, TTF_Font *font, SDL_Color fontColor) {
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

		glVertex2f(GRID_X, (500-25*GRID_HEIGHT)+i*BLOCK_DIM);
		glVertex2f(GRID_X+GRID_WIDTH*BLOCK_DIM, (500-25*GRID_HEIGHT)+i*BLOCK_DIM);

		glEnd();
	}

	// vertical lines
	for (int i = 0; i <= GRID_WIDTH; i++) {
		glBegin(GL_LINES);

		glVertex2f(GRID_X+i*BLOCK_DIM, (500-25*GRID_HEIGHT));
		glVertex2f(GRID_X+i*BLOCK_DIM, (500-25*GRID_HEIGHT)+GRID_HEIGHT*BLOCK_DIM);

		glEnd();
	}

	// white color for blocks
	glColor4ub(220, 220, 220, 255);
	(*g).displayGrid(GRID_X, 500-25*GRID_HEIGHT);

	// SCORE

	ostringstream ostr;
	ostr << score;
	const char *score_char = ostr.str().c_str();

  SDL_Rect location;
	location.x = 50;
	location.y = 25;

	SDL_GL_RenderText(score_char, font, fontColor, &location);
	
	///////////////
	// END DRAWING
	////////////////

	glPopMatrix();
	SDL_GL_SwapBuffers();
	SDL_Delay(33); // frame rate 30ms
}

void SDL_GL_RenderText(const char *text, TTF_Font *font, SDL_Color color, SDL_Rect *location)
{
	SDL_Surface *initial;
	SDL_Surface *intermediary;
	//SDL_Rect rect;
	int w,h;
	GLuint texture;
	
	/* Use SDL_TTF to render our text */
	initial = TTF_RenderText_Blended(font, text, color);
	
	/* Convert the rendered text to a known format */
	w = initial->w;
	h = initial->h;
	
	intermediary = SDL_CreateRGBSurface(0, w, h, 32, 
			0x00ff0000, 0x0000ff00, 0x000000ff, 0xff000000);

	SDL_BlitSurface(initial, 0, intermediary, 0);
	
	/* Tell GL about our new texture */
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	glTexImage2D(GL_TEXTURE_2D, 0, 4, w, h, 0, GL_BGRA, 
			GL_UNSIGNED_BYTE, intermediary->pixels );
	
	/* GL_NEAREST looks horrible, if scaled... */
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);	

	/* prepare to render our texture */
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, texture);
	glColor3f(1.0f, 1.0f, 1.0f);
	
	/* Draw a quad at location */
	glBegin(GL_QUADS);
		/* Recall that the origin is in the lower-left corner
		   That is why the TexCoords specify different corners
		   than the Vertex coors seem to. */
		glTexCoord2f(0.0f, 0.0f); 
			glVertex2f(location->x    , location->y);
		glTexCoord2f(1.0f, 0.0f); 
			glVertex2f(location->x + w, location->y);
		glTexCoord2f(1.0f, 1.0f); 
			glVertex2f(location->x + w, location->y + h);
		glTexCoord2f(0.0f, 1.0f); 
			glVertex2f(location->x    , location->y + h);
	glEnd();
	
	/* Bad things happen if we delete the texture before it finishes */
	glFinish();
	
	/* return the deltas in the unused w,h part of the rect */
	location->w = initial->w;
	location->h = initial->h;
	
	/* Clean up */
	SDL_FreeSurface(initial);
	SDL_FreeSurface(intermediary);
	glDeleteTextures(1, &texture);
}
