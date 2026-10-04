#pragma once

//Console includes
#include <Windows.h>
#include <conio.h>
#include <cstdlib>

#include <stdio.h>
#include <tchar.h>
#include <iomanip>

#include <iostream>
#include <string>
#include <sstream>
#include "Keys.h"

namespace System
{
	// Colors - can be used as Foreground or Background
	enum class ConsoleColor : byte
	{
		Black = 0,
		DarkBlue = FOREGROUND_BLUE,
		DarkGreen = FOREGROUND_GREEN,
		DarkCyan = FOREGROUND_GREEN | FOREGROUND_BLUE,
		DarkRed = FOREGROUND_RED,
		DarkMagenta = FOREGROUND_RED | FOREGROUND_BLUE,
		DarkYellow = FOREGROUND_RED | FOREGROUND_GREEN,
		Gray = FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE,
		DarkGray = FOREGROUND_INTENSITY,
		Blue = FOREGROUND_BLUE | FOREGROUND_INTENSITY,
		Green = FOREGROUND_GREEN | FOREGROUND_INTENSITY,
		Cyan = FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY,
		Red = FOREGROUND_RED | FOREGROUND_INTENSITY,
		Magenta = FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_INTENSITY,
		Yellow = FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY,
		White = FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY,
	};

	enum class RunType : byte
	{
		MainMenu,
		BitMenu,
		OctMenu,
		HexMenu,
		ExitMenu
	};

	class Console
	{
		// Data members
		static HANDLE out;
		static WORD defColors;
		static HWND hwnd;

		// Positioning
		static const int colWidth = 30;

		// Running Elements
		bool runApp;
		RunType runType;
		int left;
		int top;

		// Display Labels
		std::string bitField_Label;
		std::string hexField_Label;
		std::string octField_Label;
		std::string controls_Label;
		std::string labTitle;
		std::string leaveMsg;
		std::string& hexField;
		std::string& octField;

		// Bit Specific Info
		int& bitField;
		int& selectedBit;
		bool& bitStatus;

	public:
		// Change Keybinds Here
		static const KeyBinds KeyOn = KeyBinds::Key_I;
		static const KeyBinds KeyOff = KeyBinds::Key_O;
		static const KeyBinds KeyToggle = KeyBinds::Key_Space;
		static const KeyBinds KeyNegate = KeyBinds::Key_N;
		static const KeyBinds KeyShiftLeft = KeyBinds::Key_Q;
		static const KeyBinds KeyShiftRight = KeyBinds::Key_E;
		static const KeyBinds KeySelectorRight = KeyBinds::Key_Left;
		static const KeyBinds KeySelectorLeft = KeyBinds::Key_Right;
		static const KeyBinds KeyBitOn = KeyBinds::Key_Tab;
		static const KeyBinds KeyEscape = KeyBinds::Key_Escape;

	private:
		// Display a Unicode symbol.
		static void Show(wchar_t symbol);

		// Converts a bitField to a string variable
		static std::string BinaryToString(int bitField, int bitNumber);

		// Prints the controls for the program
		static void PrintControls();

		void DisplayMainMenu();
		void DisplayBinaryMenu();
		void DisplayHexadecimalMenu();
		void DisplayOctalMenu();
		void DisplayEditBitsMenu();
		void DisplayExitMenu();

		// Checks the status of the BitStatus and then returns a string for it
		std::string GetBitStatus();

	public:
		Console(int& _bitField, int& _selectBit, bool& _bitStatus, std::string& _hex, std::string& _oct);
		bool Init();
		bool Run();
		void Exit();

#pragma region Color 
		// Get the current foreground color
		static WORD ForegroundColor();

		// Change the foreground color
		static void ForegroundColor(WORD attr);

		// Get the current background color
		static WORD BackgroundColor();

		// Change the background color
		static void BackgroundColor(WORD attr);

		// Set the colors back to the defaults (usually gray on black)
		static void ResetColor();
#pragma endregion

#pragma region Console Dimensions
		// Get the full width of the window in cells (characters)
		static int ConsoleFullWidth();

		// Get the half width of the window in cells (characters)
		static int ConsoleHalfWidth();

		// Get the full height of the window in cells (characters)
		static int ConsoleFullHeight();

		// Get the half height of the window in cells (characters)
		static int ConsoleHalfHeight();

		// Change the size of the window
		static void SetWindowSize(SHORT columns, SHORT rows);
#pragma endregion

#pragma region Cursor
		// Get the current column of the cursor
		static int CursorLeft();

		// Get the current row of the cursor
		static int CursorTop();

		// Change the position of the cursor
		static void SetCursorPosition(SHORT left, SHORT top);

		// Set the visibility of the cursor
		static void CursorVisible(bool visible);
#pragma endregion

		// Clear the screen
		static void Clear();

		// For animation and/or to reduce flickering
		static void Lock(bool lock);

		// Prevent cin and GetAsyncKeyState() from seeing each other's input.
		static void FlushKeys();

		// Display a Unicode symbol.
		static void Show(int x, int y, wchar_t symbol);

		// Display a rectangle in the window.
		static void DrawBox(int left, int top, int width, int height, bool dbl);

		// Displays the a given menu to the user
		void DisplayMenu();

		// Prints in the center best as it can be
		static void PrintCentered(SHORT left, SHORT top, std::string message);

		static bool WasMoveSelectorRightPressed() { return GetAsyncKeyState((int)Console::KeySelectorRight); }
		static bool WasMoveSelectorLeftPressed() { return GetAsyncKeyState((int)Console::KeySelectorLeft); }
		static bool WasKeyOnPressed() { return GetAsyncKeyState((int)Console::KeyOn); }
		static bool WasKeyOffPressed() { return GetAsyncKeyState((int)Console::KeyOff); }
		static bool WasBitTogglePressed() { return GetAsyncKeyState((int)Console::KeyToggle); }
		static bool WasBitNegatePressed() { return GetAsyncKeyState((int)Console::KeyNegate); }
		static bool WasShiftRightPressed() { return GetAsyncKeyState((int)Console::KeyShiftRight); }
		static bool WasShiftLeftPressed() { return GetAsyncKeyState((int)Console::KeyShiftLeft); }
		static bool WasBitOnPressed() { return GetAsyncKeyState((int)Console::KeyBitOn) & 0x8000; }
		static bool WasExitPressed() { return GetAsyncKeyState((int)Console::KeyEscape) & 0x8000; }
	};

	std::string GetKeyBindName(KeyBinds key);

}
