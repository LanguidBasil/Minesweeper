#include <iostream>
#include "Console.h"
#include "Minesweeper/Board.h"
#include "Minesweeper/Drawer.h"

int main()
{
	Console::Init();
	const int BOARD_WIDTH = 10;
	const int BOARD_HEIGHT = 10;

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

	std::cin.get();
}
