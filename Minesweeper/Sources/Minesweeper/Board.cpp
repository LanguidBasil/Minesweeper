#include "Board.h"
#include <vector>
#include <algorithm>
#include <memory>

namespace Minesweeper
{
	Board::Board(GameSettings gameSettings)
		: WIDTH(gameSettings.BoardWidth), HEIGHT(gameSettings.BoardHeight), AMOUNT_OF_BOMBS(gameSettings.AmountOfBombs), Cells(std::vector<Cell>(WIDTH* HEIGHT))
	{
		PopulateWithBombs();
	}

	void Board::FlagCell(int posX, int posY)
	{
		auto& cell = Cells[PosToIndex(posX, posY)];

		if (cell.State != Cell::State::Open)
			cell.State = Cell::State::Flagged;
	}

	void Board::OpenCell(int posX, int posY)
	{
		Cells[PosToIndex(posX, posY)].State = Cell::State::Open;
	}

	int Board::BombsAroundCell(int posX, int posY) const
	{
		// O O O
		// O X O
		// O O O

		int bombCount = 0;
		for (auto h = -1; h < 2; h++)
		{
			for (auto w = -1; w < 2; w++)
			{
				if (h == 0 && w == 0)
					continue;

				auto currentHeight = posY + h;
				auto currentWidth = posX + w;

				if (currentHeight >= HEIGHT || 0 > currentHeight ||
					currentWidth >= WIDTH || 0 > currentWidth)
				{
					continue;
				}

				auto& currentCell = Cells[PosToIndex(currentWidth, currentHeight)];
				bombCount += currentCell.HasBomb ? 1 : 0;
			}
		}

		return bombCount;
	}

	Cell Board::GetCell(int posX, int posY) const
	{
		return Cells[PosToIndex(posX, posY)];
	}

	int Board::PosToIndex(int posX, int posY) const
	{
		return posY * WIDTH + posX;
	}

	void Board::PopulateWithBombs()
	{
		int cellAmount = WIDTH * HEIGHT;
		auto cellsIndecesWithBombs = std::vector<int>(cellAmount);

		for (auto i = 0; i < cellAmount; i++)
			cellsIndecesWithBombs[i] = i;

		// TODO: add randomness
		//std::srand(std::time)
		std::random_shuffle(std::begin(cellsIndecesWithBombs), std::end(cellsIndecesWithBombs));

		for (auto i = 0; i < AMOUNT_OF_BOMBS; i++)
			Cells[cellsIndecesWithBombs[i]].HasBomb = true;
	}
}