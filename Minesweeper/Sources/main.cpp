#include <iostream>
#include "Console.h"
#include "Minesweeper/Board.h"
#include "Minesweeper/Drawer.h"

int main()
{
	const int BOARD_WIDTH = 10;
	const int BOARD_HEIGHT = 10;
	Minesweeper::Board<BOARD_WIDTH, BOARD_HEIGHT> b;

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

	Minesweeper::Drawer<BOARD_WIDTH, BOARD_HEIGHT> d(b, ds);
	d.Draw();

	Console::SetCursorPos(14, 4);
	short yPos = 5;
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
			}
			else if (me.ButtonPressed == Console::MouseEvent::ButtonPressed::Right)
			{
				b.FlagCell(xOnBoard, yOnBoard);
			}
			d.Draw();

			std::string meMessage = std::to_string((int)me.ButtonPressed) + ' ' + std::to_string(xOnBoard) + ' ' + std::to_string(yOnBoard);
			Console::PrintMessage(14, yPos++, meMessage);
		}
	}

	Console::SetCursorPos(1, 20);
	std::cin.get();
}
