#pragma once

#include <ncurses.h>
#include <string>

namespace nce {

	/*
	 * Engine class/wrapper for the ncurses environment. To use, just
	 * create a new nce::Screen object, and it will automatically handle
	 * setting up and tearing down the curses window. It also includes some
	 * utility functions that act as wrappers for some basic curses drawing
	 * functions.
	 */
	class Screen {

	private:
		int screenWidth;
		int screenHeight;
		void setupScreen();
		void cleanupScreen();
	
	public:
		Screen();
		Screen(const Screen&);
		~Screen();
		// Upper left y, upper left x, lower right y, lower right x, color pair num
		void drawBox(int, int, int, int, int);
		// Upper left y, upper left x, lower right y, lower right x, box characters, ACS flag, color pair num
		void drawCustomBox(int, int, int, int, char *, bool, int);
		// Upper left y, upper left x, lower right y, lower right x, color pair num
		void drawFill(int, int, int, int, int);
		// y coordinate, x coordinate, text string, ncurses attributes
		void drawText(int, int, std::string, int);

	};

}
