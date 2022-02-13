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

	template <int width, int height, int amountOfBombs>
	class Board
	{
	public:
		const int WIDTH;
		const int HEIGHT;
		const int AMOUNT_OF_BOMBS;

		Board()
			: Cells(std::array<Cell, width* height>()), WIDTH(width), HEIGHT(height), AMOUNT_OF_BOMBS(amountOfBombs) {}

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
			return 0;
		}

		constexpr Cell GetCell(int posX, int posY) const
		{
			return Cells[PosToIndex(posX, posY)];
		}

	private:
		std::array<Cell, width* height> Cells;

		constexpr int PosToIndex(int posX, int posY) const
		{
			return posY * WIDTH + posX;
		}
	};
}