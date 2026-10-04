#ifndef KEYBINDS_H
#define KEYBINDS_H

enum class KeyBinds : byte
{
	// Alphabet keys
	Key_A = 0x41,  // 'A' key
	Key_B = 0x42,  // 'B' key
	Key_C = 0x43,  // 'C' kezy
	Key_D = 0x44,  // 'D' key
	Key_E = 0x45,  // 'E' key
	Key_F = 0x46,  // 'F' key
	Key_G = 0x47,  // 'G' key
	Key_H = 0x48,  // 'H' key
	Key_I = 0x49,  // 'I' key
	Key_J = 0x4A,  // 'J' key
	Key_K = 0x4B,  // 'K' key
	Key_L = 0x4C,  // 'L' key
	Key_M = 0x4D,  // 'M' key
	Key_N = 0x4E,  // 'N' key
	Key_O = 0x4F,  // 'O' key
	Key_P = 0x50,  // 'P' key
	Key_Q = 0x51,  // 'Q' key
	Key_R = 0x52,  // 'R' key
	Key_S = 0x53,  // 'S' key
	Key_T = 0x54,  // 'T' key
	Key_U = 0x55,  // 'U' key
	Key_V = 0x56,  // 'V' key
	Key_W = 0x57,  // 'W' key
	Key_X = 0x58,  // 'X' key
	Key_Y = 0x59,  // 'Y' key
	Key_Z = 0x5A,  // 'Z' key

	// Numeric keys
	Key_0 = 0x30,  // '0' key
	Key_1 = 0x31,  // '1' key
	Key_2 = 0x32,  // '2' key
	Key_3 = 0x33,  // '3' key
	Key_4 = 0x34,  // '4' key
	Key_5 = 0x35,  // '5' key
	Key_6 = 0x36,  // '6' key
	Key_7 = 0x37,  // '7' key
	Key_8 = 0x38,  // '8' key
	Key_9 = 0x39,  // '9' key

	Key_NumPad0 = 0x60,
	Key_NumPad1 = 0x61,
	Key_NumPad2 = 0x62,
	Key_NumPad3 = 0x63,
	Key_NumPad4 = 0x64,
	Key_NumPad5 = 0x65,
	Key_NumPad6 = 0x66,
	Key_NumPad7 = 0x67,
	Key_NumPad8 = 0x68,
	Key_NumPad9 = 0x69,

	// Function keys
	Key_F1 = 0x70,
	Key_F2 = 0x71,
	Key_F3 = 0x72,
	Key_F4 = 0x73,
	Key_F5 = 0x74,
	Key_F6 = 0x75,
	Key_F7 = 0x76,
	Key_F8 = 0x77,
	Key_F9 = 0x78,
	Key_F10 = 0x79,
	Key_F11 = 0x7A,
	Key_F12 = 0x7B,

	// Special keys
	Key_Backspace = 0x08,   // Backspace key
	Key_Tab = 0x09,         // Tab key
	Key_Enter = 0x0D,       // Enter key
	Key_Shift = 0x10,       // Shift key
	Key_Ctrl = 0x11,        // Ctrl key
	Key_Alt = 0x12,         // Alt key
	Key_Escape = 0x1B,      // Escape key
	Key_Space = 0x20,       // Space bar
	Key_Left = 0x25,        // Left arrow
	Key_Up = 0x26,          // Up arrow
	Key_Right = 0x27,       // Right arrow
	Key_Down = 0x28,        // Down arrow

	// Additional keys
	Key_Insert = 0x2D,
	Key_Delete = 0x2E,
	Key_Home = 0x24,
	Key_End = 0x23,
	Key_PageUp = 0x21,
	Key_PageDown = 0x22,
	Key_NumLock = 0x90,
	Key_CapsLock = 0x14
};

#endif