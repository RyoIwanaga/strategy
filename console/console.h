#ifndef _strategy__console_h_
#define _strategy__console_h_

#include <cassert>
#include "../WorldInfo.h"
#include "../reu.h"

#define NS_CONSOLE namespace console {
#define NS_CONSOLE_END }

NS_CONSOLE;
NS_USING_STRATEGY;

#include <ncurses.h>

enum class Color : short {
	TerrainOutOfSight = 1,
	TerrainOcean,
	TerrainGlassland,
	Player1 = 10,
	Player2,
	Player3,
	Player4,
	Player5,
	Player6,
	Player7,
	Player8,
};

void initColorTerrain()
{
	init_pair(static_cast<short>(Color::TerrainOutOfSight), COLOR_WHITE, COLOR_BLACK);
	init_pair(static_cast<short>(Color::TerrainOcean), COLOR_BLUE, COLOR_BLACK);
	init_pair(static_cast<short>(Color::TerrainGlassland), COLOR_GREEN, COLOR_BLACK);
}

short _makeColorTerrain(const Terrain& t)
{
	switch(t.getBase()) {
	case Terrain::BaseType::Ocean:
		return static_cast<short>(Color::TerrainOcean);
	case Terrain::BaseType::Glassland:
		return static_cast<short>(Color::TerrainGlassland);
	default:
		assert(false);
	}
}

chtype makeColorTerrain(const Terrain& t)
{
	return COLOR_PAIR(_makeColorTerrain(t));
}

chtype makeColorTerrainOutOfSight()
{
	return COLOR_PAIR(static_cast<short>(Color::TerrainOutOfSight));
}

chtype makeColorPlayer(ushort player)
{
	return COLOR_PAIR(player + 10);
}

void initialize()
{
	// The very first thing to do: Before you use any other curses routines, the initscr() routine must be called first.
	// If your program is going to write to several terminals, you should call newterm instead, which is another story.
	initscr(); 

	// One-character-a-time. To disable the buffering of typed characters by the TTY driver and get a character-at-a-time input, you need to call
    cbreak(); 

	// No echo. To suppress the automatic echoing of typed characters, you need to call
    noecho(); 

	// Special keys. In order to capture special keystrokes like Backspace, Delete and the four arrow keys by getch(), you need to call
	keypad(stdscr, TRUE); 

	start_color();

	initColorTerrain();

	
	init_pair(static_cast<int>(Color::Player1), COLOR_WHITE, COLOR_BLUE);
	init_pair(static_cast<int>(Color::Player2), COLOR_WHITE, COLOR_RED);
	init_pair(static_cast<int>(Color::Player3), COLOR_WHITE, COLOR_YELLOW);
}

void finalize ()
{
	// Before exiting. Before the program is terminated, endwin() must be called to restore the terminal settings. 
	endwin();
}


NS_CONSOLE_END;

#include "Window.h"
#include "WindowWorld.h"
#include "WindowMessage.h"

#endif // _Console_h_

