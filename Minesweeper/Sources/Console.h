#pragma once

#include <Windows.h>

namespace Console
{
	extern const HANDLE ConsoleOutput;

	void Init();
	void PrintSquareSolid(short cursorPosX, short cursorPosY, short width, short height);
	void PrintSquareHollow(short cursorPosX, short cursorPosY, short width, short height);
};