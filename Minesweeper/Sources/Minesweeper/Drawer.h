#pragma once

#include "../Console.h"
#include "Board.h"
#include "GameEnd.h"
#include "../Utils/EventTimer.h"

namespace Minesweeper
{
	struct DrawerSettings
	{
		Console::Color ColorFrame       = Console::Color::White;
		Console::Color ColorCellOpen    = Console::Color::White;
		Console::Color ColorCellClosed  = Console::Color::White;
		Console::Color ColorCellFlagged = Console::Color::White;

		int BoardStartPositionX = 0;
		int BoardStartPositionY = 0;

		int TextStartPositionX = 0;
		int TextStartPositionY = 0;
	};

	class Drawer
	{
	public:
		Drawer(const Minesweeper::Board& board, const DrawerSettings& drawerSettings, std::shared_ptr<Utils::EventTimer> timer);
		~Drawer();

		void DrawBoard() const;

		void DrawTimer(Utils::EventTimerArgs args) const;

		void DrawGameEnd(GameEnd gameEnd) const;

		const DrawerSettings& GetDrawerSettings() const;

	private:
		const Minesweeper::Board& Board;
		const DrawerSettings Settings;
		const std::shared_ptr<Utils::EventTimer> Timer;

		constexpr Console::Color ColorOfBombCount(int bombsAroundCell) const;

		static std::string GameEndToMessage(GameEnd gameEnd);
	};
}