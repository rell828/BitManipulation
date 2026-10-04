#include "Console.h"

// All parameters should use one of the following,
//	- bitField
//		- The field of bits that you are manipulating
//  - bitIndex 
//		- The position of the bit that you are manipulating

// TODO: Create a TurnOn method
// TODO: Create a TurnOff method
// TODO: Create a Toggle method
// TODO: Create a IsBitOn method
// TODO: Create a Negate method
// TODO: Create a LeftShift method
// TODO: Create a RightShift method

// OPTIONAL - 
// You can implement this method
//		void ToHex(int bitField, std::string& displayField);
// You can implement this method
//		void ToOct(int bitField, std::string& displayField);

/*
	YOU SHOULD - only be adding to the code via:
		- Creating/Calling methods
		- Passing Parameters
		- Manipulating Data using bit shifting

	DO NOT:
		- Modify/Remove any methods being called already.
			This will result in a 0.
		- Be using
			- std::bitset
			- std::oct
			- std::hex
			- std::stringstream
*/
// TurnOn
void TurnOn(int& bitField, int bitIndex)
{
	bitField = bitField | (1 << bitIndex);
}

// TurnOff
void TurnOff(int& bitField, int bitIndex)
{
	bitField = bitField & ~(1 << bitIndex);
}

// Toggle
void Toggle(int& bitField, int bitIndex)
{
	bitField = bitField ^ (1 << bitIndex);
}

// IsBitOn
bool IsBitOn(int bitField, int bitIndex)
{
	return (bitField & (1 << bitIndex)) != 0;
}

// Negate
void Negate(int& bitField)
{
	bitField = ~bitField;
}

// LeftShift
void LeftShift(int& bitField)
{
	bitField = bitField << 1;
}

// RightShift
void RightShift(int& bitField)
{
	bitField = bitField >> 1;
}
int main()
{
	int mBitField = 0;
	int mBitIndex = 0;
	std::string mHexField = "0";
	std::string mOctField = "0";
	bool run = 1;
	bool bitStatus = 0;

	System::Console app = System::Console(mBitField, mBitIndex, bitStatus, mHexField, mOctField);
	if (!app.Init()) return -1;

	while (app.Run())
	{
		// DO NOT REMOVE THIS LINE:
		app.DisplayMenu();

		_getch();

		if (System::Console::WasMoveSelectorRightPressed())
		{
			if (mBitIndex < 31) ++mBitIndex;
		}
		if (System::Console::WasMoveSelectorLeftPressed())
		{
			if (mBitIndex > 0) --mBitIndex;
		}
		if (System::Console::WasKeyOnPressed())
		{
			// Implement the TurnOn Method
			TurnOn(mBitField, mBitIndex);
		}
		if (System::Console::WasKeyOffPressed())
		{
			// Implement the TurnOff Method
			TurnOff(mBitField, mBitIndex);
		}
		if (System::Console::WasBitTogglePressed())
		{
			// Implement the Toggle Method
			Toggle(mBitField, mBitIndex);
		}
		if (System::Console::WasBitNegatePressed())
		{
			// Implement the Negate Method
			
		}
		if (System::Console::WasShiftLeftPressed())
		{
			// Implement the LeftShift Method
			Negate(mBitField);
		}
		if (System::Console::WasShiftRightPressed())
		{
			// Implement the RightShift Method
			LeftShift(mBitField);
		}

		// Implement the IsBitOn method. Store the result into the bitStatus member field.
		bitStatus = IsBitOn(mBitField, mBitIndex);

		// OPTIONAL - Implement the ToHex method

		// OPTIONAL - Implement the ToOct method

	}
	app.Exit();

	//Visual Studios will add this for us when building C++ projects but best to be explicit 
	//You never know when you'll be working in another IDE that may not do the same
	return 0;
}