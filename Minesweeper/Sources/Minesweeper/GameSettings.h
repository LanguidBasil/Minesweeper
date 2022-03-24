#pragma once
#include <chrono>

namespace Minesweeper
{
	struct GameSettings
	{
		int BoardWidth		   = 10;
		int BoardHeight		   = 10;
		int AmountOfBombs      = 100;
		std::chrono::seconds TimeBeforeGameOver = std::chrono::seconds(60);
	};
}