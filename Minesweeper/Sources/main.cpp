#include "Minesweeper/Minesweeper.h"
#include "Console.h"

int main()
{
	Console::ConsoleSettings consoleSettings;
	{
		consoleSettings.ConsoleWidth = 50;
		consoleSettings.ConsoleHeight = 50;
		consoleSettings.FontWidth = 12;
		consoleSettings.FontHeight = 12;
		consoleSettings.ConsoleTitle = "Minesweeper";
	}
	Console::Init(consoleSettings);

	// TODO: add menu screen
	Minesweeper::StartGame();
}
