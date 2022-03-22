#pragma once

#include "GameSettings.h"
#include <vector>

namespace Minesweeper
{
	struct Cell
	{
		enum struct State
		{
			Closed,
			Open,
			Flagged
		};

		bool HasBomb = false;
		State State  = State::Closed;
	};

	class Board
	{
	public:
		const int WIDTH;
		const int HEIGHT;
		const int AMOUNT_OF_BOMBS;


		Board(GameSettings gameSettings);

		void FlagCell(int posX, int posY);

		void OpenCell(int posX, int posY);

		int BombsAroundCell(int posX, int posY) const;

		Cell GetCell(int posX, int posY) const;

	private:
		std::vector<Cell> Cells;

		int PosToIndex(int posX, int posY) const;

		void PopulateWithBombs();
	};
}