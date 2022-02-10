#include <iostream>
#include "Console.h"
#include "Minesweeper/Board.h"
#include "Minesweeper/Drawer.h"

int main()
{
	const int BOARD_WIDTH = 10;
	const int BOARD_HEIGHT = 10;

	Console::ConsoleSettings cs;
	cs.ConsoleWidth = 40;
	cs.ConsoleHeight = 40;
	cs.FontWidth = 12;
	cs.FontHeight = 12;
	cs.ConsoleTitle = "Minesweeper";
	Console::Init(cs);

	Minesweeper::Board<BOARD_WIDTH, BOARD_HEIGHT> b;
	b.FlagCell(0, 0);
	b.OpenCell(1, 0);
	b.OpenCell(2, 7);

	Minesweeper::DrawerSettings ds;
	ds.ColorFrame = Console::Color::DarkGray;
	ds.ColorCellClosed = Console::Color::White;
	ds.ColorCellFlagged = Console::Color::DarkRed;
	ds.ColorCellOpen = Console::Color::BrightGray;
	ds.BoardStartPositionX = 1;
	ds.BoardStartPositionY = 1;
	ds.TextStartPositionX = 14;
	ds.TextStartPositionY = 1;

	Minesweeper::Drawer<BOARD_WIDTH, BOARD_HEIGHT> d(b, ds);
	d.Draw();

	Console::SetCursorPos(14, 4);

	std::cin.get();
}
