#include "Drawer.h"

namespace Minesweeper
{
	Drawer::Drawer(const Minesweeper::Board& board, const DrawerSettings& drawerSettings, std::shared_ptr<Utils::EventTimer> timer)
		: Board(board), Settings(drawerSettings), Timer(timer)
	{
		Timer->Event += std::bind(&Drawer::DrawTimer, this, std::placeholders::_1);
	}

	Drawer::~Drawer()
	{
		Timer->Event -= std::bind(&Drawer::DrawTimer, this, std::placeholders::_1);
	}

	void Drawer::DrawBoard() const
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

	void Drawer::DrawTimer(Utils::EventTimerArgs args) const
	{
		std::string message = "Time passed: " + std::to_string(args.TotalPassedTime.count() / 1000) + '\n';

		Console::ChangeColor(Console::Color::White, Console::Color::Black);
		Console::PrintMessage(Settings.TextStartPositionX, Settings.TextStartPositionY, message);
	}

	void Drawer::DrawGameEnd(GameEnd gameEnd) const
	{
		Console::ChangeColor(Console::Color::White, Console::Color::Black);
		Console::PrintMessage(Settings.TextStartPositionX, Settings.TextStartPositionY + 1, GameEndToMessage(gameEnd) + '\n');
	}

	const DrawerSettings& Drawer::GetDrawerSettings() const
	{
		return Settings;
	}

	constexpr Console::Color Drawer::ColorOfBombCount(int bombsAroundCell) const
	{
		if (bombsAroundCell == 0)
			return Settings.ColorCellOpen;
		return Console::Color::BrightBlue;
	}

	std::string Drawer::GameEndToMessage(GameEnd gameEnd)
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
}