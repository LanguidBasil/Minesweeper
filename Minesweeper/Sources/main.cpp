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

	Minesweeper::Drawer<BOARD_WIDTH, BOARD_HEIGHT> d(b);
	d.Draw();

	std::cin.get();
}
