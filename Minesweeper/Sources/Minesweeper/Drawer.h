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
			: Board(b), DrawerSettings(drawerSettings) {}

		void Draw() const
		{
			int boardXStart = DrawerSettings.BoardStartPositionX;
			int boardYStart = DrawerSettings.BoardStartPositionY;

			Console::ChangeColor(DrawerSettings.ColorFrame, Console::Color::Black);
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
						Console::ChangeColor(DrawerSettings.ColorCellClosed, Console::Color::Black);
						Console::PrintSquareSolid(w + boardXStart + 1, h + boardYStart + 1, 1, 1);
						break;

					case Minesweeper::Cell::State::Flagged:
						Console::ChangeColor(DrawerSettings.ColorCellFlagged, Console::Color::Black);
						Console::PrintSquareSolid(w + boardXStart + 1, h + boardYStart + 1, 1, 1);
						break;

					case Minesweeper::Cell::State::Open:
						bombsAroundCell = Board.BombsAroundCell(w, h);
						fontColor = ColorOfBombCount(bombsAroundCell);

						Console::ChangeColor(fontColor, DrawerSettings.ColorCellOpen);
						Console::PrintMessage(w + boardXStart + 1, h + boardYStart + 1, std::to_string(bombsAroundCell));
						break;

					default:
						break;
					}
				}
			}

			int textXStart = DrawerSettings.TextStartPositionX;
			int textYStart = DrawerSettings.TextStartPositionY;

			Console::ChangeColor(Console::Color::White, Console::Color::Black);
			Console::PrintMessage(textXStart, textYStart, "Bombs left: 13");
			Console::PrintMessage(textXStart, textYStart + 1, "Time left: 87\n");
		}

	private:
		const Minesweeper::Board<width, height, amountOfBombs>& Board;
		const DrawerSettings DrawerSettings;

		constexpr Console::Color ColorOfBombCount(int bombsAroundCell) const
		{
			if (bombsAroundCell == 0)
				return DrawerSettings.ColorCellOpen;
			return Console::Color::BrightBlue;
		}
	};
}