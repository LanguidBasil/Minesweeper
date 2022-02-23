#pragma once

#include <Windows.h>
#include <string>

namespace Console
{
	enum struct Color
	{
		Black		  = 0,
		DarkGray	  = 8,
		BrightGray	  = 7,
		White		  = 15,

		DarkBlue	  = 1,
		DarkGreen	  = 2,
		DarkCyan	  = 3,
		DarkRed		  = 4,
		DarkMagenta   = 5,
		DarkYellow	  = 6,

		BrightBlue	  = 9,
		BrightGreen   = 10,
		BrightCyan    = 11,
		BrightRed     = 12,
		BrightMagenta = 13,
		BrightYellow  = 14
	};

	struct MouseEvent
	{
		enum struct ButtonPressed
		{
			None,
			Left,
			Right
		};

		ButtonPressed ButtonPressed = ButtonPressed::None;
		int PosX = 0;
		int PosY = 0;
	};

	struct ConsoleSettings
	{
		int FontWidth  = 0;
		int FontHeight = 0;

		int ConsoleWidth  = 0;
		int ConsoleHeight = 0;

		std::string ConsoleTitle;
	};

	void Init(const ConsoleSettings& cs);
	void PrintMessage(short posX, short posY, const std::string& message);
	void PrintSquareSolid(short posX, short posY, short width, short height);
	void PrintSquareHollow(short posX, short posY, short width, short height);
	void ChangeColor(Color foregroundColor, Color backgroundColor);
	void SetCursorPos(short posX, short posY);
	MouseEvent GetMouseEvent();
};