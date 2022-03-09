#pragma once

namespace Minesweeper
{
	enum class GameEnd
	{
		Won,
		LostToBomb,
		LostToTimer
	};

	void StartGame();
}