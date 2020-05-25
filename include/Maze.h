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

class Maze {

private:
	int colorPair;
	int mazeWidth;
	int mazeHeight;
	int pathWidth;
	int * cells;
	int numVisited;
	std::stack<std::pair<int, int>> path;
	void populateCells();
	void populateMaze();
	void drawMaze();
	
public:
	Maze();
	Maze(const Maze&);
	~Maze();
	int createMaze();
	void resetMaze();

};
