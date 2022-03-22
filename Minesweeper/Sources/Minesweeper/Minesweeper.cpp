#include "Minesweeper.h"

#include <iostream>
#include "../Console.h"
#include "GameSettings.h"
#include "Board.h"
#include "Drawer.h"
#include "GameEnd.h"

static constexpr bool InBoardBounds(int posX, int posY, int boardWidth, int boardHeight)
{
	return -1 < posX && posX < boardWidth &&
		   -1 < posY && posY < boardHeight;
}

struct InputInfo
{
	Console::MouseEvent::Button PressedButton;
	bool EnconteredBomb;
};

namespace Minesweeper
{
	static void OpenCell(Board& board, int posX, int posY)
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

					if (!InBoardBounds(currentX, currentY, board.WIDTH, board.HEIGHT))
						continue;

					if (board.GetCell(currentX, currentY).State == Minesweeper::Cell::State::Closed)
						OpenCell(board, currentX, currentY);
				}
		}
	}

	static InputInfo ReceiveInput(Board& board, const DrawerSettings& drawerSettings)
	{
		auto mouseEvent = Console::GetMouseEvent();
		if (mouseEvent.ButtonPressed == Console::MouseEvent::Button::None)
			return { mouseEvent.ButtonPressed, false };

		int frameWidth = 1;
		int xOnBoard = mouseEvent.PosX - drawerSettings.BoardStartPositionX - frameWidth;
		int yOnBoard = mouseEvent.PosY - drawerSettings.BoardStartPositionY - frameWidth;

		if (!InBoardBounds(xOnBoard, yOnBoard, board.WIDTH, board.HEIGHT))
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
		Console::ConsoleSettings consoleSettings;
		{
			consoleSettings.ConsoleWidth = 40;
			consoleSettings.ConsoleHeight = 40;
			consoleSettings.FontWidth = 12;
			consoleSettings.FontHeight = 12;
			consoleSettings.ConsoleTitle = "Minesweeper";
		}

		Minesweeper::GameSettings gameSettings;
		{
			gameSettings.BoardWidth = 10;
			gameSettings.BoardHeight = 10;
			gameSettings.AmountOfBombs = 10;
			gameSettings.TimeBeforeGameOver = 60;
		}
		Minesweeper::DrawerSettings drawerSettings;
		{
			drawerSettings.ColorFrame = Console::Color::DarkGray;
			drawerSettings.ColorCellClosed = Console::Color::White;
			drawerSettings.ColorCellFlagged = Console::Color::DarkRed;
			drawerSettings.ColorCellOpen = Console::Color::BrightGray;
			drawerSettings.BoardStartPositionX = 1;
			drawerSettings.BoardStartPositionY = 1;
			drawerSettings.TextStartPositionX = 14;
			drawerSettings.TextStartPositionY = 1;
		}

		Console::Init(consoleSettings);
		auto timer = std::make_shared<Utils::EventTimer>(std::chrono::seconds(1));

		Minesweeper::Board board(gameSettings);
		Minesweeper::Drawer<BOARD_WIDTH, BOARD_HEIGHT, AMOUNT_OF_BOMBS> drawer(board, drawerSettings, timer);
		drawer.DrawBoard();

		// game loop
		while (true)
		{
			auto inputInfo = ReceiveInput(board, drawer.GetDrawerSettings());

			if (inputInfo.PressedButton == Console::MouseEvent::Button::None)
				continue;

			if (inputInfo.EnconteredBomb)
			{
				drawer.DrawBoard();
				drawer.DrawGameEnd(GameEnd::LostToBomb);
				break;
			}
			else
			{
				drawer.DrawBoard();
			}
		}

		std::cin.get();
	}
}