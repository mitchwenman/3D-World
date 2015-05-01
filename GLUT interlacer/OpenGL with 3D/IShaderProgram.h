#pragma once

class IShaderProgram
{
public:
	virtual void useProgram() = 0;

	unsigned int programId;
};