#pragma once

class IShaderProgram
{
public:
	//! Virtual method to load the program prior to the object being rendered.
	//! Subclasses must implement this.
	virtual void useProgram() = 0;

	//! The id of the program returned by glCreateProgram
	unsigned int programId;
};