#include <iostream>
#include "Console.h";

int main()
{
	Console::Init();
	Console::PrintSquareSolid(1, 1, 10, 10);
	Console::PrintSquareHollow(12, 1, 10, 10);
	Console::PrintMessage(13, 2, "Yo");
}
