#pragma once

namespace Minesweeper
{
	struct GameSettings
	{
		int BoardWidth		   = 10;
		int BoardHeight		   = 10;
		int AmountOfBombs      = 100;
		int TimeBeforeGameOver = 60;
	};
}