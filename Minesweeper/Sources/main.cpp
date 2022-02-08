#include <iostream>
#include "Console.h"
#include "Board.h"

int main()
{
	Console::Init();

	Minesweeper::Board<10, 10> b;
	b.FlagCell(0, 0);

	Console::ChangeColor(Console::Color::DarkGray, Console::Color::Black);
	Console::PrintSquareHollow(1, 1, 12, 12);
	Console::ChangeColor(Console::Color::White, Console::Color::Black);
	Console::PrintSquareSolid(2, 2, 10, 10);

	Console::ChangeColor(Console::Color::White, Console::Color::Black);
	Console::PrintMessage(1, 14, "Bombs left: 13");
	Console::PrintMessage(1, 15, "Time left: 87\n");

	std::cin.get();
}
