#include "Minesweeper/Minesweeper.h"
#include "Console.h"
#include "Utils/EventTimer.h"

#include <chrono>
#include <iostream>

int main()
{
	// TODO: Add timer
	// TODO: Add losing to timer
	// TODO: Add winning
	// TODO: Add difficulty

	Utils::EventTimer timer(std::chrono::seconds(1));
	timer.Event += 
	[](Utils::EventTimerArgs args) 
	{ 
		auto seconds = std::chrono::duration_cast<std::chrono::seconds>(args.TotalPassedTime).count();
		auto message = "Time passed: " + std::to_string(seconds) + 's';
		Console::ChangeColor(Console::Color::White, Console::Color::Black);
		Console::PrintMessage(16, 16, message);
	};

	Minesweeper::StartGame();
}
