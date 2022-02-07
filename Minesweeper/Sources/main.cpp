#include <iostream>
#include "Console.h";

int main()
{
	ConsoleInit();
	PrintSquareSolid(1, 1, 10, 10);
	PrintSquareHollow(12, 1, 10, 10);
	std::cout << "\n\n";
}
