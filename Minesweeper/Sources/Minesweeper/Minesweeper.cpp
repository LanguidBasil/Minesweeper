#include "Minesweeper.h"

#include "GameSettings.h"
#include "Board.h"
#include "Drawer.h"
#include "GameEnd.h"
#include <iostream>
#include <chrono>

struct InputInfo
{
	Console::MouseEvent::Button PressedButton;
	bool EnconteredBomb;
};

namespace Minesweeper
{
	static constexpr bool InBoardBounds(int posX, int posY, int boardWidth, int boardHeight)
	{
		return -1 < posX && posX < boardWidth &&
			-1 < posY && posY < boardHeight;
	}

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

	static void GameOver(Drawer& drawer, GameEnd gameEnd)
	{
		drawer.DrawBoard();
		drawer.DrawGameEnd(gameEnd);
		drawer.~Drawer();
	}

	static void GameLoop(Board& board, Drawer& drawer, const bool& lostToTime)
	{
		while (true)
		{
			if (lostToTime)
			{
				GameOver(drawer, GameEnd::LostToTimer);
				return;
			}

			auto inputInfo = ReceiveInput(board, drawer.GetDrawerSettings());

			if (inputInfo.PressedButton == Console::MouseEvent::Button::None)
				continue;

			if (inputInfo.EnconteredBomb)
			{
				GameOver(drawer, GameEnd::LostToBomb);
				return;
			}

			drawer.DrawBoard();
		}
	}

	void StartGame()
	{
		Minesweeper::GameSettings gameSettings;
		{
			gameSettings.BoardWidth = 10;
			gameSettings.BoardHeight = 10;
			gameSettings.AmountOfBombs = 10;
			gameSettings.TimeBeforeGameOver = std::chrono::seconds(60);
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

		auto timer = std::make_shared<Utils::EventTimer>(std::chrono::seconds(1));

		Minesweeper::Board board(gameSettings);
		Minesweeper::Drawer drawer(board, drawerSettings, timer);

		bool lostToTime = false;
		timer->Event += [&](Utils::EventTimerArgs args) 
			{
				lostToTime = args.TotalPassedTime > gameSettings.TimeBeforeGameOver;
			};

		drawer.DrawBoard();
		drawer.DrawTimer({ std::chrono::seconds(0), std::chrono::seconds(0) });

		GameLoop(board, drawer, lostToTime);

		std::cin.get();
	}
}