#include <iostream>
#include <Windows.h>
#include <cstring>

static const char square = 219;

HANDLE consoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);

void SetConsoleFont();
void PrintSquareSolid(short cursorPosX, short cursorPosY, short width, short height);
void PrintSquareHollow(short cursorPosX, short cursorPosY, short width, short height);

int main()
{
	SetConsoleFont();
	PrintSquareSolid(1, 1, 10, 10);
	PrintSquareHollow(12, 1, 10, 10);
	std::cout << '\n';
}

void SetConsoleFont()
{
	CONSOLE_FONT_INFOEX cfi;
	cfi.cbSize = sizeof(CONSOLE_FONT_INFOEX);
	cfi.nFont = 0;
	cfi.dwFontSize.X = 12;
	cfi.dwFontSize.Y = 12;
	cfi.FontFamily = FF_DONTCARE;
	cfi.FontWeight = FW_NORMAL;
	wcscpy_s(cfi.FaceName, L"Consolas");

	SetCurrentConsoleFontEx(consoleOutput, false, &cfi);
}

void PrintSquareSolid(short cursorPosX, short cursorPosY, short width, short height)
{
	for (auto h = 0; h < height; h++)
	{
		COORD cursorPos = { cursorPosX, cursorPosY + h };
		SetConsoleCursorPosition(consoleOutput, cursorPos);

		for (auto w = 0; w < width; w++)
			std::cout << square;
	}
}

void PrintSquareHollow(short cursorPosX, short cursorPosY, short width, short height)
{
	auto squareLine = new char[width + 1];
	for (auto i = 0; i < width; i++)
		squareLine[i] = square;
	squareLine[width] = 0;

	COORD cursorPos = { cursorPosX, cursorPosY };
	SetConsoleCursorPosition(consoleOutput, cursorPos);
	std::cout << squareLine;

	cursorPos.Y = cursorPosY + height - 1;
	SetConsoleCursorPosition(consoleOutput, cursorPos);
	std::cout << squareLine;

	for (auto h = 1; h < height - 1; h++)
	{
		cursorPos.X = cursorPosX;
		cursorPos.Y = cursorPosY + h;
		SetConsoleCursorPosition(consoleOutput, cursorPos);
		std::cout << square;

		cursorPos.X = cursorPosX + width - 1;
		cursorPos.Y = cursorPosY + h;
		SetConsoleCursorPosition(consoleOutput, cursorPos);
		std::cout << square;
	}
}