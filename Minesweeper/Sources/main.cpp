#include "Minesweeper/Minesweeper.h"
#include "EventSystem.h"

#include <iostream>

int main()
{
	// TODO: Add timer
	// TODO: Add winning
	// TODO: Add difficulty
	//Minesweeper::StartGame();

	// TODO: Add events
	EventSystem::Event e;

	e += []() { std::cout << "Hello World!\n"; };
	e.Fire();
}
