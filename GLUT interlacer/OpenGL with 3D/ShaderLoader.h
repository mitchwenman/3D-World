#pragma once

#include <string>

namespace ShaderLoader
{
	int readFile(std::string name, char* buffer, int bufferLen);

	unsigned int compile(std::string file, int shaderType);

	unsigned int link(unsigned int vertexShader, unsigned int fragmentShader);
}