#pragma once

#include <string>

namespace ShaderLoader
{
	int readFile(std::string name, char* buffer, int bufferLen);
}