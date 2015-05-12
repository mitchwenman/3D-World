#pragma once

//! A base class representing a shader program.
/*!
	This class encapsulates an interface for creating various shader programs.
	Contains a default method useProgram() which must be implemented by the subclass. This method
	should be used to set up the shader i.e. passing uniforms prior to calling glUseProgram
*/
class IShaderProgram
{
public:
	//! Virtual method to load the program prior to the object being rendered.
	//! Subclasses must implement this.
	virtual void useProgram() = 0;

	//! The id of the program returned by glCreateProgram
	unsigned int programId;
};