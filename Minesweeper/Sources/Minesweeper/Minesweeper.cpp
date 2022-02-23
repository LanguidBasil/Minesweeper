#include "Minesweeper.h"

#include <iostream>
#include "../Console.h"
#include "Board.h"
#include "Drawer.h"

static constexpr bool InBoardBounds(int posX, int posY, int boardWidth, int boardHeight)
{
	return -1 < posX && posX < boardWidth &&
		   -1 < posY && posY < boardHeight;
}

namespace Minesweeper
{
	template<int boardWidth, int boardHeight, int amountOfBombs>
	static int OpenCell(Board <boardWidth, boardHeight, amountOfBombs>& board, int posX, int posY)
	{
		board.OpenCell(posX, posY);

		if (board.GetCell(posX, posY).HasBomb)
			return -1;

		if (board.BombsAroundCell(posX, posY) == 0)
		{
			// opening cells around empty cell
			// O O O
			// O X O
			// O O O
			for (auto y = -1; y < 2; y++)
				for (auto x = -1; x < 2; x++)
				{
					if (y == 0 && x == 0)
						continue;

					auto currentX = posX + x;
					auto currentY = posY + y;

					if (!InBoardBounds(currentX, currentY, boardWidth, boardHeight))
						continue;

					if (board.GetCell(currentX, currentY).State == Minesweeper::Cell::State::Closed)
						OpenCell(board, currentX, currentY);
				}
		}

		return 0;
	}

	template<int boardWidth, int boardHeight, int amountOfBombs>
	static void ReceiveInput(Board <boardWidth, boardHeight, amountOfBombs>& board,
							 const Drawer<boardWidth, boardHeight, amountOfBombs>& drawer)
	{
		auto& drawerSettings = drawer.GetDrawerSettings();

		while (true)
		{
			auto mouseEvent = Console::GetMouseEvent();
			if (mouseEvent.ButtonPressed == Console::MouseEvent::ButtonPressed::None)
				continue;

			constexpr int frameWidth = 1;
			int xOnBoard = mouseEvent.PosX - drawerSettings.BoardStartPositionX - frameWidth;
			int yOnBoard = mouseEvent.PosY - drawerSettings.BoardStartPositionY - frameWidth;

			if (!InBoardBounds(xOnBoard, yOnBoard, boardWidth, boardHeight))
				continue;

			if (mouseEvent.ButtonPressed == Console::MouseEvent::ButtonPressed::Left)
			{
				if (OpenCell(board, xOnBoard, yOnBoard) == -1)
				{
					drawer.Draw();
					return;
				}
			}
			else if (mouseEvent.ButtonPressed == Console::MouseEvent::ButtonPressed::Right)
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
		const int AMOUNT_OF_BOMBS = 10;
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

		ReceiveInput(b, d);

		Console::ChangeColor(Console::Color::White, Console::Color::Black);
		Console::PrintMessage(ds.TextStartPositionX, ds.TextStartPositionY + 1, "Bomb! Game Over");
		std::cin.get();
	}
}