#pragma once

#include "../Console.h"
#include "Board.h"
#include "GameEnd.h"
#include "../Utils/EventTimer.h"

namespace Minesweeper
{
	struct DrawerSettings
	{
		Console::Color ColorFrame       = Console::Color::White;
		Console::Color ColorCellOpen    = Console::Color::White;
		Console::Color ColorCellClosed  = Console::Color::White;
		Console::Color ColorCellFlagged = Console::Color::White;

		int BoardStartPositionX = 0;
		int BoardStartPositionY = 0;

		int TextStartPositionX = 0;
		int TextStartPositionY = 0;
	};

	template<int width, int height, int amountOfBombs>
	class Drawer
	{
	public:
		Drawer(const Minesweeper::Board& board, const DrawerSettings& drawerSettings, std::shared_ptr<Utils::EventTimer> timer)
			: Board(board), Settings(drawerSettings), Timer(timer)
		{
			Timer->Event += std::bind(&Drawer::DrawTimer, this, std::placeholders::_1);
		}

		void DrawBoard() const
		{
			int boardXStart = Settings.BoardStartPositionX;
			int boardYStart = Settings.BoardStartPositionY;

			Console::ChangeColor(Settings.ColorFrame, Console::Color::Black);
			Console::PrintSquareHollow(boardXStart, boardYStart, 12, 12);

			for (auto h = 0; h < Board.HEIGHT; h++)
			{
				for (auto w = 0; w < Board.WIDTH; w++)
				{
					auto cell = Board.GetCell(w, h);
					Console::Color fontColor;
					int bombsAroundCell;
					switch (cell.State)
					{
					case Minesweeper::Cell::State::Closed:
						Console::ChangeColor(Settings.ColorCellClosed, Console::Color::Black);
						Console::PrintSquareSolid(w + boardXStart + 1, h + boardYStart + 1, 1, 1);
						break;

					case Minesweeper::Cell::State::Flagged:
						Console::ChangeColor(Settings.ColorCellFlagged, Console::Color::Black);
						Console::PrintSquareSolid(w + boardXStart + 1, h + boardYStart + 1, 1, 1);
						break;

					case Minesweeper::Cell::State::Open:
						if (cell.HasBomb)
						{
							Console::ChangeColor(Console::Color::DarkMagenta, Console::Color::DarkMagenta);
							Console::PrintSquareSolid(w + boardXStart + 1, h + boardYStart + 1, 1, 1);
							break;
						}

						bombsAroundCell = Board.BombsAroundCell(w, h);
						fontColor = ColorOfBombCount(bombsAroundCell);

						Console::ChangeColor(fontColor, Settings.ColorCellOpen);
						Console::PrintMessage(w + boardXStart + 1, h + boardYStart + 1, std::to_string(bombsAroundCell));
						break;

					default:
						break;
					}
				}
			}
		}

		void DrawTimer(Utils::EventTimerArgs args) const
		{
			std::string message = "Time passed: " + std::to_string(args.TotalPassedTime.count() / 1000) + '\n';

			Console::ChangeColor(Console::Color::White, Console::Color::Black);
			Console::PrintMessage(Settings.TextStartPositionX, Settings.TextStartPositionY, message);
		}

		void DrawGameEnd(GameEnd gameEnd) const
		{
			Console::ChangeColor(Console::Color::White, Console::Color::Black);
			Console::PrintMessage(Settings.TextStartPositionX, Settings.TextStartPositionY + 1, GameEndToMessage(gameEnd) + '\n');
		}

		const DrawerSettings& GetDrawerSettings() const
		{
			return Settings;
		}

	private:
		const Minesweeper::Board& Board;
		const DrawerSettings Settings;
		const std::shared_ptr<Utils::EventTimer> Timer;

		constexpr Console::Color ColorOfBombCount(int bombsAroundCell) const
		{
			if (bombsAroundCell == 0)
				return Settings.ColorCellOpen;
			return Console::Color::BrightBlue;
		}

		static constexpr std::string GameEndToMessage(GameEnd gameEnd)
		{
			switch (gameEnd)
			{
			case Minesweeper::GameEnd::Won:
				return "Game over! You won";
				break;
			case Minesweeper::GameEnd::LostToBomb:
				return "Game over! Bomb";
			case Minesweeper::GameEnd::LostToTimer:
				return "Game over! Timer expired";
			default:
				return "Invalid game end";
			}
		}
	};
}