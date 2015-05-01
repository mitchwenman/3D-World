#pragma once

class ShaderProgram
{
public:
	virtual void useProgram() = 0;

	unsigned int programId;
};