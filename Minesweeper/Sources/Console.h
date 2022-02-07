#pragma once

#include <Windows.h>
#include <string>

namespace Console
{
	extern const HANDLE ConsoleOutput;

	void Init();
	void PrintMessage(short posX, short posY, const std::string& message);
	void PrintSquareSolid(short posX, short posY, short width, short height);
	void PrintSquareHollow(short posX, short posY, short width, short height);
};