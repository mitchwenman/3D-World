#pragma once

#include "IShaderProgram.h"

class HighlightShaderProgram : public IShaderProgram
{
public:
	HighlightShaderProgram();

	void useProgram();
};