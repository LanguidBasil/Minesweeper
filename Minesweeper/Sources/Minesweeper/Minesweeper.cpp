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

static struct InputInfo
{
	Console::MouseEvent::Button PressedButton;
	bool EnconteredBomb;
};

namespace Minesweeper
{
	template<int boardWidth, int boardHeight, int amountOfBombs>
	static void OpenCell(Board <boardWidth, boardHeight, amountOfBombs>& board, int posX, int posY)
	{
		board.OpenCell(posX, posY);

		// opening cells around empty cell
		// O O O
		// O X O
		// O O O
		if (!board.GetCell(posX, posY).HasBomb && board.BombsAroundCell(posX, posY) == 0)
		{
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
	}

	template<int boardWidth, int boardHeight, int amountOfBombs>
	static InputInfo ReceiveInput(Board <boardWidth, boardHeight, amountOfBombs>& board,
							 const DrawerSettings& drawerSettings)
	{
		auto mouseEvent = Console::GetMouseEvent();
		if (mouseEvent.ButtonPressed == Console::MouseEvent::Button::None)
			return { mouseEvent.ButtonPressed, false };

		int frameWidth = 1;
		int xOnBoard = mouseEvent.PosX - drawerSettings.BoardStartPositionX - frameWidth;
		int yOnBoard = mouseEvent.PosY - drawerSettings.BoardStartPositionY - frameWidth;

		if (!InBoardBounds(xOnBoard, yOnBoard, boardWidth, boardHeight))
			return { mouseEvent.ButtonPressed, false };

		if (mouseEvent.ButtonPressed == Console::MouseEvent::Button::Left)
		{
			OpenCell(board, xOnBoard, yOnBoard);

			if (board.GetCell(xOnBoard, yOnBoard).HasBomb)
				return { mouseEvent.ButtonPressed, true };
		}
		else if (mouseEvent.ButtonPressed == Console::MouseEvent::Button::Right)
		{
			board.FlagCell(xOnBoard, yOnBoard);
		}

		return { mouseEvent.ButtonPressed, false };
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

		// game loop
		while (true)
		{
			auto inputInfo = ReceiveInput(b, d.GetDrawerSettings());

			if (inputInfo.PressedButton == Console::MouseEvent::Button::None)
				continue;

			if (inputInfo.EnconteredBomb)
			{
				d.Draw(GameEnd::LostToBomb);
				break;
			}
			else
			{
				d.Draw();
			}
		}

		std::cin.get();
	}
}