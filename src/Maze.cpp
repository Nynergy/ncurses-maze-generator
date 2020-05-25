#include <cstdlib>
#include <ctime>
#include <iostream>
#include <vector>

#include <unistd.h>

#include "Maze.h"

Maze::Maze() {

	// Seed random number generator
	srand(time(NULL));

	this->colorPair = (rand() % 5) + 1;

	this->mazeWidth = COLS / 2;
	this->mazeHeight = LINES / 2;
	this->pathWidth = 1;
	this->cells = new int[this->mazeWidth * this->mazeHeight];
	this->populateCells();
	this->numVisited = 0;

	// Lambda function for calculating a cell's index
	auto index = [&](int y, int x) {
		int ret = (this->path.top().first + y) * this->mazeWidth + (this->path.top().second + x);
		return ret;
	};

	int randX = rand() % this->mazeWidth;
	int randY = rand() % this->mazeHeight;

	this->path.push(std::make_pair(randY, randX));
	this->cells[index(randY, randX)] = CELL_VISITED;
	this->numVisited++;

}

Maze::Maze(const Maze& other) {

	this->colorPair = other.colorPair;;

	this->mazeWidth = other.mazeWidth;
	this->mazeHeight = other.mazeHeight;
	this->pathWidth = other.pathWidth;
	this->cells = new int[this->mazeWidth * this->mazeHeight];
	for(int i = 0; i < (this->mazeWidth * this->mazeHeight); i++) {
		this->cells[i] = other.cells[i];
	}
	this->numVisited = other.numVisited;

	this->path = other.path;

}

Maze::~Maze() {

	delete[] this->cells;

}

void Maze::populateCells() {

	for(int i = 0; i < (this->mazeWidth * this->mazeHeight); i++) {
		this->cells[i] = 0x00;
	}

	return;

}

int Maze::createMaze() {

	// Populate the screen with unexcavated blocks
	this->populateMaze();

	// Lambda function for calculating a cell's index
	auto index = [&](int y, int x) {
		int ret = (this->path.top().first + y) * this->mazeWidth + (this->path.top().second + x);
		return ret;
	};

	// Create the maze recursively with backtracking
	while(this->numVisited < (this->mazeWidth * this->mazeHeight)) {
		// STEP ONE: Create a set of the unvisited neighbors

		std::vector<int> neighbors;

		// North Neighbor
		if(this->path.top().first > 0 && (this->cells[index(-1, 0)] & CELL_VISITED) == 0)
			neighbors.push_back(0);
		// East Neighbor
		if(this->path.top().second < this->mazeWidth - 1 && (this->cells[index(0, 1)] & CELL_VISITED) == 0)
			neighbors.push_back(1);
		// South Neighbor
		if(this->path.top().first < this->mazeHeight - 1 && (this->cells[index(1, 0)] & CELL_VISITED) == 0)
			neighbors.push_back(2);
		// West Neighbor
		if(this->path.top().second > 0 && (this->cells[index(0, -1)] & CELL_VISITED) == 0)
			neighbors.push_back(3);

		// Check if there are neighbors available
		if(!neighbors.empty()) {
			// Choose one available neighbor at random
			int nextCellDir = neighbors[rand() % neighbors.size()];

			// Set the path between the neighbor and the current cell
			switch(nextCellDir) {
				case 0: // North
					this->cells[index(0, 0)] |= CELL_PATH_N;
					this->cells[index(-1, 0)] |= CELL_PATH_S;
					this->path.push(std::make_pair((this->path.top().first - 1), (this->path.top().second + 0)));
					break;
				case 1: // East
					this->cells[index(0, 0)] |= CELL_PATH_E;
					this->cells[index(0, 1)] |= CELL_PATH_W;
					this->path.push(std::make_pair((this->path.top().first + 0), (this->path.top().second + 1)));
					break;
				case 2: // South
					this->cells[index(0, 0)] |= CELL_PATH_S;
					this->cells[index(1, 0)] |= CELL_PATH_N;
					this->path.push(std::make_pair((this->path.top().first + 1), (this->path.top().second + 0)));
					break;
				case 3: // West
					this->cells[index(0, 0)] |= CELL_PATH_W;
					this->cells[index(0, -1)] |= CELL_PATH_E;
					this->path.push(std::make_pair((this->path.top().first + 0), (this->path.top().second - 1)));
					break;
			}

			// Set current cell as visited and increment value
			this->cells[index(0, 0)] |= CELL_VISITED;
			this->numVisited++;
		} else {
			// Backtrack
			this->path.pop();
		}

		refresh();
		usleep(10000);
		this->drawMaze();

		if(getch() != ERR) {
			return 1;
		}
	}
	
	return 0;

}

void Maze::populateMaze() {

	// Fill screen with uncarved blocks
	for(int x = 0; x < (this->mazeWidth * 2); x++) {
		for(int y = 0; y < (this->mazeHeight * 2); y++) {
			attron(COLOR_PAIR(this->colorPair) | A_ALTCHARSET);
			move(y, x);
			addch(ACS_BLOCK);
			attroff(COLOR_PAIR(this->colorPair) | A_ALTCHARSET);
		}
	}

	return;

}

void Maze::drawMaze() {

	// Draw cells and their connecting paths
	for(int x = 0; x < this->mazeWidth; x++) {
		for(int y = 0; y < this->mazeHeight; y++) {
			if(this->cells[y * this->mazeWidth + x] & CELL_VISITED) {
				mvprintw(y * (this->pathWidth + 1), x * (this->pathWidth + 1), " ");
			} else {
				attron(COLOR_PAIR(this->colorPair) | A_ALTCHARSET);
				move(y * (this->pathWidth + 1), x * (this->pathWidth + 1));
				addch(ACS_BLOCK);
				attroff(COLOR_PAIR(this->colorPair) | A_ALTCHARSET);
			}

			// Draw paths between cells if a path exists
			if(this->cells[y * this->mazeWidth + x] & CELL_PATH_S) {
				mvprintw(y * (this->pathWidth + 1) + 1, x * (this->pathWidth + 1), " ");
			}

			if(this->cells[y * this->mazeWidth + x] & CELL_PATH_E) {
				mvprintw(y * (this->pathWidth + 1), x * (this->pathWidth + 1) + 1, " ");
			}
		}
	}

	return;

}

void Maze::resetMaze() {

	this->populateCells();

	// Reset maze color
	this->colorPair = (rand() % 5) + 1;

	this->numVisited = 0;

	// Lambda function for calculating a cell's index
	auto index = [&](int y, int x) {
		int ret = (this->path.top().first + y) * this->mazeWidth + (this->path.top().second + x);
		return ret;
	};

	int randX = rand() % this->mazeWidth;
	int randY = rand() % this->mazeHeight;

	this->path.push(std::make_pair(randY, randX));
	this->cells[index(randY, randX)] = CELL_VISITED;
	this->numVisited++;

	return;

}
