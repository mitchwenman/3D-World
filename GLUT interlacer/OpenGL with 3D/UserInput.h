#pragma once

//! Groups together user input functions.
namespace UserInput
{
	//! Handles the logic for all user key inputs.
	//! @sideeffect A world object's transformation vector may be modified.
	//! @param c The character that was pressed by the user.
	//! @param x The x coordindate of the mouse when the key was pressed.
	//! @param y The y coordinate of the mouse when the key was pressed.
	void handleKeyInput(unsigned char c, int x, int y);

	//! Handles the logic for special key presses i.e. arrow keys
	//! @sideeffect The position and/or rotation of the camera may be modified.
	//! @param c The character that was pressed by the user.
	//! @param x The x coordindate of the mouse when the key was pressed.
	//! @param y The y coordinate of the mouse when the key was pressed.
	void handleSpecialKeyInput(unsigned char c, int x, int y);
};