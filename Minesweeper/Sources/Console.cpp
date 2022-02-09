#include "Console.h";

#include <iostream>
#include <string>
#include <Windows.h>
#include <cstring>

static const char SQUARE = 219;

namespace Console
{
	static const HANDLE ConsoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);

	static void SetConsoleFont(short fontWidth, short fontHeight)
	{
		CONSOLE_FONT_INFOEX cfi;
		cfi.cbSize = sizeof(CONSOLE_FONT_INFOEX);
		cfi.nFont = 0;
		cfi.dwFontSize = { fontWidth, fontHeight };
		cfi.FontFamily = FF_DONTCARE;
		cfi.FontWeight = FW_NORMAL;
		wcscpy_s(cfi.FaceName, L"Consolas");

		SetCurrentConsoleFontEx(ConsoleOutput, false, &cfi);
	}

	static void SetConsoleSize(int xOffset, int yOffset, int width, int height, int fontWidth, int fontHeight)
	{
		SMALL_RECT windowSize = { 0, 0, width, height };

		SetConsoleWindowInfo(ConsoleOutput, true, &windowSize);
		MoveWindow(GetConsoleWindow(), xOffset, yOffset, 20 * fontWidth, 30 * fontHeight, true);
	}

	static constexpr WORD ColorToWord(Color foregroundColor, Color backgroundColor)
	{
		return (int)foregroundColor + (int)backgroundColor * 16;
	}

	void Init()
	{
		COORD fontSize = { 12, 12 };
		COORD consoleSize = { 25, 30 };
		LPCSTR consoleTitle = "Minesweeper";

		SetConsoleTitleA(consoleTitle);
		SetConsoleSize(100, 80, consoleSize.X, consoleSize.Y, fontSize.X, fontSize.Y);

		SetConsoleFont(fontSize.X, fontSize.Y);
	}

	void PrintMessage(short posX, short posY, const std::string& message)
	{
		SetConsoleCursorPosition(ConsoleOutput, { posX, posY });
		std::cout << message;
	}

	void PrintSquareSolid(short posX, short posY, short width, short height)
	{
		for (auto h = 0; h < height; h++)
		{
			COORD cursorPos = { posX, posY + h };
			SetConsoleCursorPosition(ConsoleOutput, cursorPos);

			for (auto w = 0; w < width; w++)
				std::cout << SQUARE;
		}
	}

	void PrintSquareHollow(short posX, short posY, short width, short height)
	{
		auto squareLine = std::string(width, SQUARE);

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
			std::cout << SQUARE;

			cursorPos.X = posX + width - 1;
			cursorPos.Y = posY + h;
			SetConsoleCursorPosition(ConsoleOutput, cursorPos);
			std::cout << SQUARE;
		}
	}

	void ChangeColor(Color foregroundColor, Color backgroundColor)
	{
		WORD color = ColorToWord(foregroundColor, backgroundColor);
		SetConsoleTextAttribute(ConsoleOutput, color);
	}
}