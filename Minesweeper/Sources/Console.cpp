#include "Console.h";

#include <iostream>
#include <string>
#include <Windows.h>
#include <cstring>

static const char square = 219;

namespace Console
{
	static void SetConsoleFont()
	{
		CONSOLE_FONT_INFOEX cfi;
		cfi.cbSize = sizeof(CONSOLE_FONT_INFOEX);
		cfi.nFont = 0;
		cfi.dwFontSize.X = 12;
		cfi.dwFontSize.Y = 12;
		cfi.FontFamily = FF_DONTCARE;
		cfi.FontWeight = FW_NORMAL;
		wcscpy_s(cfi.FaceName, L"Consolas");

		SetCurrentConsoleFontEx(ConsoleOutput, false, &cfi);
	}

	const HANDLE ConsoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);

	void Console::Init()
	{
		SetConsoleFont();
	}

	void Console::PrintMessage(short posX, short posY, const std::string& message)
	{
		SetConsoleCursorPosition(ConsoleOutput, { posX, posY });
		std::cout << message;
	}

	void Console::PrintSquareSolid(short posX, short posY, short width, short height)
	{
		for (auto h = 0; h < height; h++)
		{
			COORD cursorPos = { posX, posY + h };
			SetConsoleCursorPosition(ConsoleOutput, cursorPos);

			for (auto w = 0; w < width; w++)
				std::cout << square;
		}
	}

	void Console::PrintSquareHollow(short posX, short posY, short width, short height)
	{
		auto squareLine = new char[width + 1];
		for (auto i = 0; i < width; i++)
			squareLine[i] = square;
		squareLine[width] = 0;

		COORD cursorPos = { posX, posY };
		SetConsoleCursorPosition(ConsoleOutput, cursorPos);
		std::cout << squareLine;

		cursorPos.Y = posY + height - 1;
		SetConsoleCursorPosition(ConsoleOutput, cursorPos);
		std::cout << squareLine;

		for (auto h = 1; h < height - 1; h++)
		{
			cursorPos.X = posX;
			cursorPos.Y = posY + h;
			SetConsoleCursorPosition(ConsoleOutput, cursorPos);
			std::cout << square;

			cursorPos.X = posX + width - 1;
			cursorPos.Y = posY + h;
			SetConsoleCursorPosition(ConsoleOutput, cursorPos);
			std::cout << square;
		}
	}
}