#include "Console.h"

namespace System
{
	HANDLE Console::out = GetStdHandle(STD_OUTPUT_HANDLE);
	WORD Console::defColors = Console::BackgroundColor() << 4 | Console::ForegroundColor();
	HWND Console::hwnd = GetConsoleWindow();

	void Console::Show(wchar_t symbol)
	{
		std::wcout << symbol;
	}

	WORD Console::ForegroundColor()
	{
		CONSOLE_SCREEN_BUFFER_INFO info;
		GetConsoleScreenBufferInfo(out, &info);
		return info.wAttributes & 0x0F;
	}

	void Console::ForegroundColor(WORD attr)
	{
		CONSOLE_SCREEN_BUFFER_INFO info;
		GetConsoleScreenBufferInfo(out, &info);
		SetConsoleTextAttribute(out, info.wAttributes & 0xF0 | attr);
	}

	WORD Console::BackgroundColor()
	{
		CONSOLE_SCREEN_BUFFER_INFO info;
		GetConsoleScreenBufferInfo(out, &info);
		return (info.wAttributes & 0xF0) >> 4;
	}

	void Console::BackgroundColor(WORD attr)
	{
		CONSOLE_SCREEN_BUFFER_INFO info;
		GetConsoleScreenBufferInfo(out, &info);
		SetConsoleTextAttribute(out, info.wAttributes & 0x0F | attr << 4);
	}

	void Console::ResetColor()
	{
		SetConsoleTextAttribute(out, defColors);
	}

	int Console::ConsoleFullWidth()
	{
		CONSOLE_SCREEN_BUFFER_INFO info;
		GetConsoleScreenBufferInfo(out, &info);
		return info.srWindow.Right - info.srWindow.Left + 1;
	}

	int Console::ConsoleHalfWidth()
	{
		return (int)(ConsoleFullWidth() * 0.5f);
	}

	int Console::ConsoleFullHeight()
	{
		CONSOLE_SCREEN_BUFFER_INFO info;
		GetConsoleScreenBufferInfo(out, &info);
		return info.srWindow.Bottom - info.srWindow.Top + 1;
	}

	int Console::ConsoleHalfHeight()
	{
		return (int)(ConsoleFullHeight() * 0.5f);
	}

	void Console::SetWindowSize(SHORT columns, SHORT rows)
	{
		COORD c = GetLargestConsoleWindowSize(out);
		if (columns < 1 || columns > c.X)
			columns = c.X;
		if (rows < 1 || rows > c.Y)
			rows = c.Y;

		SMALL_RECT dim = { 0, 0, columns - 1, rows - 1 };
		SetConsoleWindowInfo(out, TRUE, &dim);
	}

	void Console::CursorVisible(bool visible)
	{
		CONSOLE_CURSOR_INFO curs;
		GetConsoleCursorInfo(out, &curs);
		if (curs.bVisible == TRUE && visible || curs.bVisible == FALSE && !visible)
			return;
		curs.bVisible = (visible) ? TRUE : FALSE;
		SetConsoleCursorInfo(out, &curs);
	}

	void Console::Clear()
	{
		CONSOLE_SCREEN_BUFFER_INFO info;
		GetConsoleScreenBufferInfo(out, &info);

		DWORD len = info.dwSize.X, num;
		COORD c = { 0, 0, };
		for (int i = 0; i < info.dwSize.Y; ++i)
		{
			c.Y = i;
			FillConsoleOutputAttribute(out, info.wAttributes, len, c, &num);
			FillConsoleOutputCharacter(out, ' ', len, c, &num);
		}

		SetCursorPosition(0, 0);
	}

	int Console::CursorLeft()
	{
		CONSOLE_SCREEN_BUFFER_INFO info;
		GetConsoleScreenBufferInfo(out, &info);
		return info.dwCursorPosition.X;
	}

	int Console::CursorTop()
	{
		CONSOLE_SCREEN_BUFFER_INFO info;
		GetConsoleScreenBufferInfo(out, &info);
		return info.dwCursorPosition.Y;
	}

	void Console::SetCursorPosition(SHORT left, SHORT top)
	{
		CONSOLE_SCREEN_BUFFER_INFO info;
		GetConsoleScreenBufferInfo(out, &info);

		left = max(left, 0);
		left = min(left, info.dwSize.X - 1);
		top = max(top, 0);
		top = min(top, info.dwSize.Y - 1);

		COORD cp = { left, top, };
		SetConsoleCursorPosition(out, cp);
	}

	void Console::Lock(bool lock)
	{
		LockWindowUpdate(lock ? hwnd : nullptr);
	}

	void Console::FlushKeys()
	{
		for (int i = 0; i < 256; ++i) GetAsyncKeyState(i);
		while (_kbhit()) _getch();
	}

	void Console::Show(int x, int y, wchar_t symbol)
	{
		static bool imbued;
		if (!imbued)
		{
			std::wcout.imbue(std::locale(".OCP"));
			imbued = true;
		}
		SetCursorPosition(x, y);
		Show(symbol);
	}

	void Console::DrawBox(int left, int top, int width, int height, bool dbl)
	{
		wchar_t const* SingleLine = L"┌─┐│└┘",
			* DoubleLine = L"╔═╗║╚╝",
			* Set = dbl ? DoubleLine : SingleLine;

		Show(left, top, Set[0]);
		for (int col = 0; col < width - 2; col++)
			Show(Set[1]);
		Show(Set[2]);

		int x = left + width - 1, y = top + 1;
		for (int row = 0; row < height - 2; row++, y++)
		{
			Show(left, y, Set[3]);
			Show(x, y, Set[3]);
		}

		y = top + height - 1;
		Show(left, y, Set[4]);
		for (int col = 0; col < width - 2; col++)
			Show(Set[1]);
		Show(Set[5]);
	}

	void Console::PrintControls()
	{
		std::string control_ON = GetKeyBindName(KeyOn) + ": Turn On";
		std::string control_OFF = GetKeyBindName(KeyOff) + ": Turn Off";
		std::string control_TOGGLE = GetKeyBindName(KeyToggle) + ": Toggle Bit";
		std::string control_NEGATE = GetKeyBindName(KeyNegate) + ": Negate";
		std::string control_LSHIFT = GetKeyBindName(KeyShiftLeft) + ": Shift Left";
		std::string control_RSHIFT = GetKeyBindName(KeyShiftRight) + ": Shift Right";
		std::string control_RMOVE = GetKeyBindName(KeySelectorRight) + ": Move Right";
		std::string control_LMOVE = GetKeyBindName(KeySelectorLeft) + ": Move Left";
		std::string control_ESC = GetKeyBindName(KeyEscape) + ": Main Menu";

		int left = ConsoleHalfWidth() - 22;

		SetCursorPosition(left, CursorTop() + 1);
		std::cout << std::left;

		std::cout << std::setw(colWidth) << control_ON << control_OFF << std::endl;
		SetCursorPosition(left, CursorTop());
		std::cout << std::setw(colWidth) << control_TOGGLE << control_NEGATE << std::endl;
		SetCursorPosition(left, CursorTop());
		std::cout << std::setw(colWidth) << control_LSHIFT << control_RSHIFT << std::endl;
		SetCursorPosition(left, CursorTop());
		std::cout << std::setw(colWidth) << control_LMOVE << control_RMOVE << std::endl;
		SetCursorPosition(left, CursorTop());
		std::cout << std::setw(colWidth) << control_ESC << std::endl;
	}

	void Console::DisplayMenu()
	{
		// Prepare Renderer
		system("cls");

		switch (runType)
		{
		case System::RunType::MainMenu:
			DisplayMainMenu();
			break;
		case System::RunType::BitMenu:
			DisplayBinaryMenu();
			break;
		case System::RunType::OctMenu:
			DisplayOctalMenu();
			break;
		case System::RunType::HexMenu:
			DisplayHexadecimalMenu();
			break;
		case System::RunType::ExitMenu:
			DisplayExitMenu();
			break;
		default:
			break;
		}

		// Altered Top/Left points for displaying
		int left = (int)(ConsoleFullWidth() * 0.25f);
		int top = (int)(ConsoleFullHeight() * 0.25f) - 1;
		Console::DrawBox(left, top, ConsoleHalfWidth(), (ConsoleHalfHeight() + 2), true);
		Console::SetCursorPosition(0, 0);
	}

	void Console::DisplayMainMenu()
	{
		int top = (int)(ConsoleFullHeight() * 0.25f) - 1;

		std::string menu_binary = "1. Binary";
		std::string menu_hexadecimal = "2. Hexadecimal";
		std::string menu_octal = "3. Octal";
		std::string menu_esc = GetKeyBindName(KeyEscape) + ": Exit";

		PrintCentered(ConsoleHalfWidth(), top + (int)(ConsoleHalfHeight() * 0.25), labTitle);
		PrintCentered(ConsoleHalfWidth(), CursorTop() + 3, menu_binary);
		PrintCentered(ConsoleHalfWidth(), CursorTop() + 2, menu_hexadecimal);
		PrintCentered(ConsoleHalfWidth(), CursorTop() + 2, menu_octal);
		PrintCentered(ConsoleHalfWidth(), CursorTop() + 2, menu_esc);
	}

	void Console::DisplayBinaryMenu()
	{
		PrintCentered(ConsoleHalfWidth(), top + 1, bitField_Label);
		PrintCentered(ConsoleHalfWidth(), CursorTop() + 1, std::to_string(bitField));

		DisplayEditBitsMenu();
	}

	void Console::DisplayHexadecimalMenu()
	{
		PrintCentered(ConsoleHalfWidth(), top + 1, hexField_Label);
		PrintCentered(ConsoleHalfWidth(), CursorTop() + 1, hexField);

		DisplayEditBitsMenu();
		hexField.clear();
	}

	void Console::DisplayOctalMenu()
	{
		PrintCentered(ConsoleHalfWidth(), top + 1, octField_Label);
		PrintCentered(ConsoleHalfWidth(), CursorTop() + 1, octField);

		DisplayEditBitsMenu();
		octField.clear();
	}

	void Console::DisplayEditBitsMenu()
	{
		// Controls Label
		PrintCentered(ConsoleHalfWidth(), CursorTop() + 2, controls_Label);
		// Controls Require special formatting
		SetCursorPosition(left, CursorTop() + 1);
		PrintControls();

		// Bit Status 
		PrintCentered(ConsoleHalfWidth(), CursorTop() + 1, "Bit Status: " + GetBitStatus());

		// BitField: 00000000000000000000000000000000
		std::string strBits = "Bits: " + BinaryToString(bitField, 32);
		PrintCentered(ConsoleHalfWidth(), CursorTop() + 2, strBits);

		// render bit selector
		int offsetSelector = (int)((ConsoleHalfWidth() - (int)(strBits.length() * 0.5)) * 0.5) + 29 + left;
		int bitPosition = (offsetSelector - selectedBit);
		PrintCentered(bitPosition, CursorTop() + 1, "^");
	}

	void Console::DisplayExitMenu()
	{
		PrintCentered(ConsoleHalfWidth(), ConsoleHalfHeight() - 2, labTitle);
		PrintCentered(ConsoleHalfWidth(), ConsoleHalfHeight() - 1, leaveMsg);
	}

	std::string Console::GetBitStatus()
	{
		return bitStatus ? "On" : "Off";
	}

	Console::Console(int& _bitField, int& _selectBit, bool& _bitStatus, std::string& _hex, std::string& _oct) : bitField(_bitField), selectedBit(_selectBit), bitStatus(_bitStatus), hexField(_hex), octField(_oct)
	{
		// Setup run app conditions
		runApp = true;
		runType = RunType::MainMenu;

		// Setup text fields that won't change
		bitField_Label = "Bitfield Value: ";
		controls_Label = "== Controls ==";
		labTitle = "== Systems Programming - Bit Manipulation Lab ==";
		leaveMsg = "== Have a nice day! ==";
		hexField_Label = "Hex Field Value: ";
		octField_Label = "Oct Field Value: ";

		// Store values for adjusted left and right to reuse (for resizing/formatting)
		left = (int)(ConsoleFullWidth() * 0.25f);
		top = (int)(ConsoleFullHeight() * 0.25f) - 1;

		// Left Justify all output to the console
		std::cout << std::left;
	}

	bool Console::Init()
	{
		Console::SetWindowSize(150, 30);
		Console::CursorVisible(false);
		Console::Clear();
		Console::FlushKeys();

		// You will see apps have init return a bool value or int value
		// While this implentation doesn't need a bool return, we use it so
		// students can get used to the looks of it for later courses.
		return true;
	}

	bool Console::Run()
	{
		// Run update for positions if screen was resized
		left = (int)(ConsoleFullWidth() * 0.25f);
		top = (int)(ConsoleFullHeight() * 0.25f) - 1;

		// Esc was pressed, decide if it was in a menu or not
		if (GetAsyncKeyState((int)Console::KeyEscape) & 0x8000)
		{
			if (runType == RunType::MainMenu)
			{
				runApp = false;
			}
			else
			{
				runType = RunType::MainMenu;
			}
		}

		// Decide Run Type based on input while in Main Menu
		else if (runType == RunType::MainMenu)
		{
			if ((GetAsyncKeyState((int)KeyBinds::Key_1) & 0x8000) || (GetAsyncKeyState((int)KeyBinds::Key_NumPad1) & 0x8000)) {
				runType = RunType::BitMenu;
			}
			else if ((GetAsyncKeyState((int)KeyBinds::Key_2) & 0x8000) || (GetAsyncKeyState((int)KeyBinds::Key_NumPad2) & 0x8000)) {
				runType = RunType::HexMenu;
			}
			else if ((GetAsyncKeyState((int)KeyBinds::Key_3) & 0x8000) || (GetAsyncKeyState((int)KeyBinds::Key_NumPad3) & 0x8000)) {
				runType = RunType::OctMenu;
			}
			else if (GetAsyncKeyState((int)KeyBinds::Key_Escape) & 0x8000) {
				runType = RunType::ExitMenu;
			}
		}

		Console::FlushKeys();
		// Keeps Loop Alive
		return runApp;
	}

	void Console::Exit()
	{
		Console::Clear();
		Console::FlushKeys();
		Console::CursorVisible(true);

		DisplayExitMenu();
		Console::DrawBox(left, top, ConsoleHalfWidth(), (ConsoleHalfHeight() + 2), true);
		Console::SetCursorPosition(0, 0);
	}

	void Console::PrintCentered(SHORT left, SHORT top, std::string message)
	{
		SetCursorPosition(left - (int)(message.length() * 0.5f), top);
		std::cout << message;
	}

	std::string Console::BinaryToString(int num, int bits)
	{
		std::string text;
		for (int i = 0; i < bits; i++)
		{
			text = std::to_string((num >> i) & 1) + text;
		}

		text = num < 0 ? '-' + text : ' ' + text;

		return text;
	}

	// Convert Keybind to String Name
	std::string GetKeyBindName(KeyBinds key)
	{
		std::string retVal;

		switch (key)
		{
		case KeyBinds::Key_A: retVal = "A";	 break;
		case KeyBinds::Key_B: retVal = "B";	 break;
		case KeyBinds::Key_C: retVal = "C";	 break;
		case KeyBinds::Key_D: retVal = "D";	 break;
		case KeyBinds::Key_E: retVal = "E";	 break;
		case KeyBinds::Key_F: retVal = "F";	 break;
		case KeyBinds::Key_G: retVal = "G";	 break;
		case KeyBinds::Key_H: retVal = "H";	 break;
		case KeyBinds::Key_I: retVal = "I";	 break;
		case KeyBinds::Key_J: retVal = "J";	 break;
		case KeyBinds::Key_K: retVal = "K";	 break;
		case KeyBinds::Key_L: retVal = "L";	 break;
		case KeyBinds::Key_M: retVal = "M";	 break;
		case KeyBinds::Key_N: retVal = "N";	 break;
		case KeyBinds::Key_O: retVal = "O";	 break;
		case KeyBinds::Key_P: retVal = "P";	 break;
		case KeyBinds::Key_Q: retVal = "Q";	 break;
		case KeyBinds::Key_R: retVal = "R";	 break;
		case KeyBinds::Key_S: retVal = "S";	 break;
		case KeyBinds::Key_T: retVal = "T";	 break;
		case KeyBinds::Key_U: retVal = "U";	 break;
		case KeyBinds::Key_V: retVal = "V";	 break;
		case KeyBinds::Key_W: retVal = "W";	 break;
		case KeyBinds::Key_X: retVal = "X";	 break;
		case KeyBinds::Key_Y: retVal = "Y";	 break;
		case KeyBinds::Key_Z: retVal = "Z";	 break;

		case KeyBinds::Key_0: retVal = "0";	 break;
		case KeyBinds::Key_1: retVal = "1";	 break;
		case KeyBinds::Key_2: retVal = "2";	 break;
		case KeyBinds::Key_3: retVal = "3";	 break;
		case KeyBinds::Key_4: retVal = "4";	 break;
		case KeyBinds::Key_5: retVal = "5";	 break;
		case KeyBinds::Key_6: retVal = "6";	 break;
		case KeyBinds::Key_7: retVal = "7";	 break;
		case KeyBinds::Key_8: retVal = "8";	 break;
		case KeyBinds::Key_9: retVal = "9";	 break;

		case KeyBinds::Key_F1: retVal = "F1"; break;
		case KeyBinds::Key_F2: retVal = "F2"; break;
		case KeyBinds::Key_F3: retVal = "F3"; break;
		case KeyBinds::Key_F4: retVal = "F4"; break;
		case KeyBinds::Key_F5: retVal = "F5"; break;
		case KeyBinds::Key_F6: retVal = "F6"; break;
		case KeyBinds::Key_F7: retVal = "F7"; break;
		case KeyBinds::Key_F8: retVal = "F8"; break;
		case KeyBinds::Key_F9: retVal = "F9"; break;
		case KeyBinds::Key_F10: retVal = "F10";	 break;
		case KeyBinds::Key_F11: retVal = "F11";	 break;
		case KeyBinds::Key_F12: retVal = "F12";	 break;

		case KeyBinds::Key_Space: retVal = "Space"; break;
		case KeyBinds::Key_Backspace: retVal = "ESC"; break;
		case KeyBinds::Key_Tab: retVal = "Tab"; break;
		case KeyBinds::Key_Enter: retVal = "Enter"; break;
		case KeyBinds::Key_Shift: retVal = "Shift"; break;
		case KeyBinds::Key_Ctrl: retVal = "Ctrl"; break;
		case KeyBinds::Key_Alt: retVal = "Alt"; break;
		case KeyBinds::Key_Escape: retVal = "Escape"; break;
		case KeyBinds::Key_Left: retVal = "<"; break;
		case KeyBinds::Key_Up: retVal = "Up"; break;
		case KeyBinds::Key_Right: retVal = ">"; break;
		case KeyBinds::Key_Down: retVal = "Down"; break;
		default: retVal = "Unknown Key"; break;
		}

		return retVal;
	}

}
