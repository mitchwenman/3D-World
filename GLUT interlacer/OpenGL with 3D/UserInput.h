#pragma once

//! Groups together user input functions.
namespace UserInput
{
	//! Handles the logic for all user key inputs.
	//! @param c The character that was pressed by the user.
	//! @param x The x coordindate of the mouse when the key was pressed.
	//! @param The y coordinate of the mouse when the key was pressed.
	void handleKeyInput(unsigned char c, int x, int y);
}