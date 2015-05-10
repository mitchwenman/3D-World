#pragma once

#include <string>

//! Groups together functions for the loading of a GLSL shader.
namespace ShaderLoader
{
	//! Reads the file into the character buffer.
	//! @param name The path to the file.
	//! @param buffer The character buffer that will store the file.
	//! @param bufferLen The length of buffer.
	//! @return The length of the file.
	int readFile(std::string name, char* buffer, int bufferLen);

	//! Compiles the shader program by invoking glCreateShader
	//! @param file The shader file path.
	//! @param shaderType The type of shader. Either vertex or fragment shader.
	//! return The shader id returned by glCreateShader.
	unsigned int compile(std::string file, int shaderType);

	//! Creates a shader program by linking s
	unsigned int link(unsigned int vertexShader, unsigned int fragmentShader);
};