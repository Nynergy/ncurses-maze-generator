#include <unistd.h>

#include "Maze.h"
#include "Screen.h"

int main() {

	// Create Screen and Maze objects
	nce::Screen env = nce::Screen();
	Maze maze = Maze();

	nodelay(stdscr, TRUE);
	int interrupt = 0;

	while(true) {
		// Create maze
		interrupt = maze.createMaze();

		if(interrupt) {
			break;
		}

		refresh();
		usleep(1000000);

		// Reset maze to be made again
		maze.resetMaze();
	}

	return 0;

}
