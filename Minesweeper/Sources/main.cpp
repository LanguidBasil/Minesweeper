#include <iostream>
#include "Console.h"
#include "Board.h"

Console::Color ColorOfBombCount(int bombsAroundCell)
{
	return Console::Color::BrightBlue;
}

int main()
{
	Console::Init();

	Minesweeper::Board<10, 10> b;
	b.FlagCell(0, 0);
	b.OpenCell(1, 0);
	b.OpenCell(2, 7);

	Console::ChangeColor(Console::Color::DarkGray, Console::Color::Black);
	Console::PrintSquareHollow(1, 1, 12, 12);

	for (auto h = 0; h < b.Height; h++)
	{
		for (auto w = 0; w < b.Width; w++)
		{
			auto cell = b.GetCell(w, h);
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
				bombsAroundCell = b.BombsAroundCell(w, h);
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

	std::cin.get();
}
