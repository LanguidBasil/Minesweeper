#include <iostream>
#include "Console.h"
#include "Minesweeper/Board.h"
#include "Minesweeper/Drawer.h"

int main()
{
	const int BOARD_WIDTH = 10;
	const int BOARD_HEIGHT = 10;
	const int AMOUNT_OF_BOMBS = 20;
	Minesweeper::Board<BOARD_WIDTH, BOARD_HEIGHT, AMOUNT_OF_BOMBS> b;

	Console::ConsoleSettings cs;
	{
		cs.ConsoleWidth = 40;
		cs.ConsoleHeight = 40;
		cs.FontWidth = 12;
		cs.FontHeight = 12;
		cs.ConsoleTitle = "Minesweeper";
		Console::Init(cs);
	}

	Minesweeper::DrawerSettings ds;
	{
		ds.ColorFrame = Console::Color::DarkGray;
		ds.ColorCellClosed = Console::Color::White;
		ds.ColorCellFlagged = Console::Color::DarkRed;
		ds.ColorCellOpen = Console::Color::BrightGray;
		ds.BoardStartPositionX = 1;
		ds.BoardStartPositionY = 1;
		ds.TextStartPositionX = 14;
		ds.TextStartPositionY = 1;
	}

	Minesweeper::Drawer<BOARD_WIDTH, BOARD_HEIGHT, AMOUNT_OF_BOMBS> d(b, ds);
	d.Draw();

	Console::SetCursorPos(14, 4);
	while (true)
	{
		auto me = Console::GetCursorEvent();
		if (me.ButtonPressed == Console::MouseEvent::ButtonPressed::None)
			continue;

		int xOnBoard = me.PosX - ds.BoardStartPositionX - 1;
		int yOnBoard = me.PosY - ds.BoardStartPositionY - 1;
		if (-1 < xOnBoard && xOnBoard < BOARD_WIDTH &&
			-1 < yOnBoard && yOnBoard < BOARD_HEIGHT)
		{
			if (me.ButtonPressed == Console::MouseEvent::ButtonPressed::Left)
			{
				b.OpenCell(xOnBoard, yOnBoard);
				auto cell = b.GetCell(xOnBoard, yOnBoard);

				if (cell.HasBomb)
				{
					d.Draw();
					break;
				}
			}
			else if (me.ButtonPressed == Console::MouseEvent::ButtonPressed::Right)
			{
				b.FlagCell(xOnBoard, yOnBoard);
			}

			d.Draw();
		}
	}

	Console::SetCursorPos(1, 20);
	std::cin.get();
}
