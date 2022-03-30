#include "Minesweeper/Minesweeper.h"
#include "Console.h"
#include <iostream>

void PrintMenu()
{
	auto message =
R"(Welcome to Minesweeper!

Game Rules:
To win you have to find and flag all cells that contain bombs
Number on a cell represents amount of bombs around that cell
If you will open a cell that contains bomb you lose

Game Controlls:
Left click to open a cell
Right clicl to flag a cell

Game Conditions:
You have 10*10 grid with 10 bombs on it
Also you have a 60 second time limit, if time expires you lose

Good luck!)";
	std::cout << message << '\n' << "To start a game enter any key: ";
}

int main()
{
	Console::ConsoleSettings consoleSettings;
	{
		consoleSettings.ConsoleWidth = 80;
		consoleSettings.ConsoleHeight = 50;
		consoleSettings.FontWidth = 12;
		consoleSettings.FontHeight = 12;
		consoleSettings.ConsoleTitle = "Minesweeper";
	}
	Console::Init(consoleSettings);

	Console::ChangeColor(Console::Color::White, Console::Color::Black);
	PrintMenu();
	std::cin.get();
	Console::Clear();

	bool wantToContinue = true;
	while (wantToContinue)
	{
		Minesweeper::StartGame();
		Console::Clear();

		Console::ChangeColor(Console::Color::White, Console::Color::Black);
		Console::PrintMessage(0, 0, "Press y to start new game");
		char input;
		std::cin.get(input);
		wantToContinue = toupper(input) == 'Y';
	}
}
