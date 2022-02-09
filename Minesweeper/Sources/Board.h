#pragma once

#include <array>

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

		bool HasMine;
		State State;

		Cell()
			: HasMine(false), State(State::Closed) {}
	};

	template <int width, int height>
	class Board
	{
	public:
		const int Width;
		const int Height;

		Board()
			: Cells(std::array<Cell, width* height>()), Width(width), Height(height) {}

		void FlagCell(int posX, int posY)
		{
			Cells[PosToIndex(posX, posY)].State = Cell::State::Flagged;
		}

		void OpenCell(int posX, int posY)
		{
			Cells[PosToIndex(posX, posY)].State = Cell::State::Open;
		}

		constexpr int BombsAroundCell(int posX, int posY) const
		{
			return 1;
		}

		constexpr Cell GetCell(int posX, int posY) const
		{
			return Cells[PosToIndex(posX, posY)];
		}

	private:
		std::array<Cell, width* height> Cells;

		constexpr int PosToIndex(int posX, int posY) const
		{
			return posY * Width + posX;
		}
	};
}