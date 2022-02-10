#pragma once

#include "../Console.h"
#include "Board.h"

namespace Minesweeper
{
	template<int width, int height>
	class Drawer
	{
	public:
		explicit Drawer(const Minesweeper::Board<width, height>& b)
			: Board(b) {}

		void Draw() const
		{
			Console::ChangeColor(Console::Color::DarkGray, Console::Color::Black);
			Console::PrintSquareHollow(1, 1, 12, 12);

			for (auto h = 0; h < Board.Height; h++)
			{
				for (auto w = 0; w < Board.Width; w++)
				{
					auto cell = Board.GetCell(w, h);
					Console::Color fontColor;
					int bombsAroundCell;
					switch (cell.State)
					{
					case Minesweeper::Cell::State::Closed:
						Console::ChangeColor(Console::Color::White, Console::Color::Black);
						Console::PrintSquareHollow(w + 2, h + 2, 1, 1);
						break;

					case Minesweeper::Cell::State::Flagged:
						Console::ChangeColor(Console::Color::DarkRed, Console::Color::Black);
						Console::PrintSquareHollow(w + 2, h + 2, 1, 1);
						break;

					case Minesweeper::Cell::State::Open:
						bombsAroundCell = Board.BombsAroundCell(w, h);
						fontColor = ColorOfBombCount(bombsAroundCell);
						Console::ChangeColor(fontColor, Console::Color::BrightGray);
						Console::PrintMessage(w + 2, h + 2, std::to_string(bombsAroundCell));
						break;

					default:
						break;
					}
				}
			}

			Console::ChangeColor(Console::Color::White, Console::Color::Black);
			Console::PrintMessage(1, 14, "Bombs left: 13");
			Console::PrintMessage(1, 15, "Time left: 87\n");
		}

	private:
		const Minesweeper::Board<width, height> Board;

		constexpr Console::Color ColorOfBombCount(int bombsAroundCell) const
		{
			return Console::Color::BrightBlue;
		}
	};
}