#include <iostream>
#include "Console.h";

int main()
{
	Console::Init();
	Console::ChangeColor(Console::Color::BrightMagenta, Console::Color::Black);
	Console::PrintSquareSolid(0, 0, 26, 10);
	//Console::ChangeColor(Console::Color::BrightCyan, Console::Color::Black);
	//Console::PrintSquareHollow(12, 0, 10, 10);
	Console::ChangeColor(Console::Color::White, Console::Color::Black);
	Console::PrintMessage(0, 11, "Yo");
	std::cout << '\n';
}
