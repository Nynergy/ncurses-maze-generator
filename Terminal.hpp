#pragma once

#include <ncurses.h>
#include <stack>

enum {

	CELL_PATH_N = 0x01,
	CELL_PATH_E = 0x02,
	CELL_PATH_S = 0x04,
	CELL_PATH_W = 0x08,
	CELL_VISITED = 0x10,

};

class Terminal {

private:
	int colorPair;
	int mazeWidth;
	int mazeHeight;
	int pathWidth;
	int * cells;
	int numVisited;
	std::stack<std::pair<int, int>> path;
	void setupScreen();
	void cleanupScreen();
	void populateCells();
	void populateMaze();
	void drawMaze();
	
public:
	Terminal();
	Terminal(const Terminal&);
	~Terminal();
	int createMaze();
	void resetMaze();

};
