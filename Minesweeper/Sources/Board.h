#pragma once

#include <array>

namespace Minesweeper
{
	struct Cell
	{
		bool HasMine;
		enum struct State
		{
			Closed,
			Open,
			Flagged
		};
	};

	template <int width, int height>
	class Board
	{
	public:
		void FlagCell(int posX, int posY)
		{

		}

		void OpenCell(int posX, int posY)
		{

		}

		constexpr int BombsAroundCell(int posX, int posY) const
		{
			return 0;
		}

	private:
		std::array<Cell, width* height> Cells;
	};
}