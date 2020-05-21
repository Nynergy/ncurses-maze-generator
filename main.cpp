#include <ncurses.h>

#include <unistd.h>

#include "Terminal.hpp"

#define MIDHEIGHT	(LINES/2)
#define MIDWIDTH	(COLS/2)

int main() {

	// Create Terminal object
	Terminal terminal = Terminal();

	nodelay(stdscr, TRUE);
	int interrupt = 0;

	while(true) {
		// Create maze
		interrupt = terminal.createMaze();

		if(interrupt) {
			break;
		}

		refresh();
		usleep(1000000);

		// Reset maze to be made again
		terminal.resetMaze();
	}

	return 0;

}
