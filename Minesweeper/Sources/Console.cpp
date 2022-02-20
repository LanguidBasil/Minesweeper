#include "Console.h"

#include <iostream>
#include <string>
#include <array>
#include <Windows.h>
#include <cstring>

static const unsigned char SQUARE = 219;

namespace Console
{
	static const HANDLE ConsoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);
	static const HANDLE ConsoleInput = GetStdHandle(STD_INPUT_HANDLE);

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

	static void SetConsoleSize(short xOffset, short yOffset, short width, short height, short fontWidth, short fontHeight)
	{
		SMALL_RECT windowSize = { 0, 0, width, height };

		SetConsoleWindowInfo(ConsoleOutput, true, &windowSize);
		MoveWindow(GetConsoleWindow(), xOffset, yOffset, width * fontWidth, height * fontHeight, true);
	}

	static constexpr WORD ColorToWord(Color foregroundColor, Color backgroundColor)
	{
		return (int)foregroundColor + (int)backgroundColor * 16;
	}

	void Init(const ConsoleSettings& cs)
	{
		// TODO: sustain font size on window resize
		SetConsoleMode(ConsoleInput, ENABLE_EXTENDED_FLAGS | ENABLE_MOUSE_INPUT);

		SetConsoleTitleA(cs.ConsoleTitle.c_str());
		SetConsoleSize(100, 80, cs.ConsoleWidth, cs.ConsoleHeight, cs.FontWidth, cs.FontHeight);

		SetConsoleFont(cs.FontWidth, cs.FontHeight);
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

	void SetCursorPos(short posX, short posY)
	{
		SetConsoleCursorPosition(ConsoleOutput, { posX, posY });
	}

	MouseEvent GetMouseEvent()
	{
		MouseEvent me;
		DWORD amountOfInputEventsRead;
		std::array<INPUT_RECORD, 64> inputs;

		if (!ReadConsoleInput(ConsoleInput, inputs.data(), inputs.size(), &amountOfInputEventsRead))
			return { MouseEvent::ButtonPressed::None, 0, 0 };

		for (auto i = 0; i < amountOfInputEventsRead; i++)
		{
			if (inputs[i].EventType != MOUSE_EVENT)
				continue;

			const auto& mouseEventRecord = inputs[i].Event.MouseEvent;
			switch (mouseEventRecord.dwButtonState)
			{
			case FROM_LEFT_1ST_BUTTON_PRESSED:
				me.ButtonPressed = MouseEvent::ButtonPressed::Left;
				break;

			case RIGHTMOST_BUTTON_PRESSED:
				me.ButtonPressed = MouseEvent::ButtonPressed::Right;
				break;

			default:
				me.ButtonPressed = MouseEvent::ButtonPressed::None;
				break;
			}
			me.PosX = mouseEventRecord.dwMousePosition.X;
			me.PosY = mouseEventRecord.dwMousePosition.Y;
			return me;
		}

		return { MouseEvent::ButtonPressed::None, 0, 0 };
	}
}