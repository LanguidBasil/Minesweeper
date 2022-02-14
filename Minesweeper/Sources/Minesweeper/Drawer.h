#pragma once

#include "../Console.h"
#include "Board.h"

namespace Minesweeper
{
	struct DrawerSettings
	{
		Console::Color ColorFrame;
		Console::Color ColorCellOpen;
		Console::Color ColorCellClosed;
		Console::Color ColorCellFlagged;

		int BoardStartPositionX;
		int BoardStartPositionY;

		int TextStartPositionX;
		int TextStartPositionY;
	};

	template<int width, int height, int amountOfBombs>
	class Drawer
	{
	public:
		explicit Drawer(const Minesweeper::Board<width, height, amountOfBombs>& b, const DrawerSettings& drawerSettings)
			: Board(b), Settings(drawerSettings) {}

		void Draw() const
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

			int textXStart = Settings.TextStartPositionX;
			int textYStart = Settings.TextStartPositionY;

			Console::ChangeColor(Console::Color::White, Console::Color::Black);
			Console::PrintMessage(textXStart, textYStart, "Bombs left: 13");
			Console::PrintMessage(textXStart, textYStart + 1, "Time left: 87\n");
		}

		const DrawerSettings& GetDrawerSettings() const
		{
			return Settings;
		}

	private:
		const Minesweeper::Board<width, height, amountOfBombs>& Board;
		const DrawerSettings Settings;

		// TODO add different colors
		constexpr Console::Color ColorOfBombCount(int bombsAroundCell) const
		{
			if (bombsAroundCell == 0)
				return Settings.ColorCellOpen;
			return Console::Color::BrightBlue;
		}
	};
}