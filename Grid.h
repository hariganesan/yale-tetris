//Hari Ganesan 12/19/12
// Grid library file for yale-tetris

#include <iostream>
#include <string>

class Grid {
	private:
		int height; // grid dimension
		int width; // grid dimension
		int currentHeight; // height of highest filled box
		int currentSpeed; // current speed
	public:
		Grid(const int& h, const int& w);
		
		int getCurrentHeight();
		void fillGrid(); // fill grid with 1s
		void printGrid();
};
