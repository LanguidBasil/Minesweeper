#include "Minesweeper.h"

#include <iostream>
#include "../Console.h"
#include "Board.h"
#include "Drawer.h"

namespace Minesweeper
{
	template<int boardWidth, int boardHeight, int amountOfBombs>
	void ReceiveInput(Board <boardWidth, boardHeight, amountOfBombs>& board,
					  const Drawer<boardWidth, boardHeight, amountOfBombs>& drawer)
	{
		auto& drawerSettings = drawer.GetDrawerSettings();

		// TODO on clicking empty cell with no bombs around it, automatically open adjacent cells
		while (true)
		{
			auto me = Console::GetCursorEvent();
			if (me.ButtonPressed == Console::MouseEvent::ButtonPressed::None)
				continue;

			int xOnBoard = me.PosX - drawerSettings.BoardStartPositionX - 1;
			int yOnBoard = me.PosY - drawerSettings.BoardStartPositionY - 1;

			if (xOnBoard < 0 || boardWidth  <= xOnBoard ||
				yOnBoard < 0 || boardHeight <= yOnBoard)
				continue;

			if (me.ButtonPressed == Console::MouseEvent::ButtonPressed::Left)
			{
				board.OpenCell(xOnBoard, yOnBoard);
				auto cell = board.GetCell(xOnBoard, yOnBoard);

				if (cell.HasBomb)
				{
					drawer.Draw();
					return;
				}
			}
			else if (me.ButtonPressed == Console::MouseEvent::ButtonPressed::Right)
			{
				board.FlagCell(xOnBoard, yOnBoard);
			}

			drawer.Draw();
		}
	}

	void StartGame()
	{
		const int BOARD_WIDTH = 10;
		const int BOARD_HEIGHT = 10;
		const int AMOUNT_OF_BOMBS = 20;
		Console::ConsoleSettings cs;
		{
			cs.ConsoleWidth = 40;
			cs.ConsoleHeight = 40;
			cs.FontWidth = 12;
			cs.FontHeight = 12;
			cs.ConsoleTitle = "Minesweeper";
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

		Console::Init(cs);
		Minesweeper::Board<BOARD_WIDTH, BOARD_HEIGHT, AMOUNT_OF_BOMBS> b;
		Minesweeper::Drawer<BOARD_WIDTH, BOARD_HEIGHT, AMOUNT_OF_BOMBS> d(b, ds);
		d.Draw();

		// TODO move input else there
		ReceiveInput(b, d);

		Console::PrintMessage(1, ds.BoardStartPositionY + BOARD_HEIGHT + 2, "Bomb! Game Over");
		std::cin.get();
	}
}