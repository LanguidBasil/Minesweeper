#pragma once

#include <array>
#include <algorithm>

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

		bool HasBomb;
		State State;

		Cell()
			: HasBomb(false), State(State::Closed) {}
	};

	template <int width, int height, int amountOfBombs>
	class Board
	{
	public:
		const int WIDTH;
		const int HEIGHT;
		const int AMOUNT_OF_BOMBS;

		Board()
			: Cells(std::array<Cell, width * height>()), WIDTH(width), HEIGHT(height), AMOUNT_OF_BOMBS(amountOfBombs)
		{
			constexpr int cellAmount = width * height;
			std::array<int, cellAmount> cellsIndecesWithBombs {};

			for (auto i = 0; i < cellAmount; i++)
				cellsIndecesWithBombs[i] = i;

			std::random_shuffle(std::begin(cellsIndecesWithBombs), std::end(cellsIndecesWithBombs));

			for (auto i = 0; i < amountOfBombs; i++)
				Cells[cellsIndecesWithBombs[i]].HasBomb = true;
		}

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

			int bombCount = 0;
			for (auto h = -1; h < 2; h++)
			{
				for (auto w = -1; w < 2; w++)
				{
					auto currentHeight = posY + h;
					auto currentWidth  = posX + w;

					if (-1 < currentHeight || currentHeight >= HEIGHT ||
						-1 < currentWidth  || currentWidth  >= WIDTH)
					{
						continue;
					}

					auto currentCell = Cells[PosToIndex(currentWidth, currentHeight)];
					bombCount += currentCell.HasBomb ? 1 : 0;
				}
			}

			return bombCount;
		}

		constexpr Cell GetCell(int posX, int posY) const
		{
			return Cells[PosToIndex(posX, posY)];
		}

	private:
		std::array<Cell, width * height> Cells;

		constexpr int PosToIndex(int posX, int posY) const
		{
			return posY * WIDTH + posX;
		}
	};
}