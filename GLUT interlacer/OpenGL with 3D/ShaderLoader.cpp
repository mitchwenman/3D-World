#include "ShaderLoader.h"

#include <iostream>
#include "libs\glew.h"
#include "libs\glut.h"


int ShaderLoader::readFile(std::string name, char* buffer, int bufferLen)
{
	FILE* file = fopen(name.c_str(), "r");
	if (!file) //Bail out of program if can't find file
	{
		std::cout << "Can't find shading file. " << std::endl;
		exit(1); 
	}
	int rd = fread(buffer, 1, bufferLen, file);
	fclose(file);
	return rd;
}

unsigned int ShaderLoader::compile(std::string file, int shaderType)
{
	char buffer[10002];
	int read = ShaderLoader::readFile(file, buffer, 10000);
	buffer[read] = NULL;

	GLuint shader = glCreateShader(shaderType);
	if (shader == 0)
	{
		std::cout << "Shader not created. Exiting" << std::endl;
		exit(1);
	}
	
	const char* bufst = (const char*)buffer;
	glShaderSource(shader, 1, &bufst, &read); ///XXX: may not work, diff proc call to lab
	glCompileShader(shader);

	//Error checking
	int params;
	glGetShaderiv(shader, GL_COMPILE_STATUS, &params);
	if (params != GL_TRUE)
	{
		std::cout << "Shader error" << std::endl;
		if (params > 0)
		{
			char* message = (char*)malloc(params);
			glGetShaderInfoLog(shader, params, &read, message);
			std::cout << message << std::endl;
			free(message);
		}
	}
	return shader;
}

unsigned int ShaderLoader::link(unsigned int vertexShader, unsigned int fragmentShader)
{
	unsigned int program = glCreateProgram();

	if (program == 0)
	{
		std::cout << "couldn't create program" << std::endl;
		exit(1);
	}

	glAttachShader(program, vertexShader);
	glAttachShader(program, fragmentShader);

	glLinkProgram(program);

	int params;
	glGetProgramiv(program, GL_LINK_STATUS, &params);
	if (params != GL_TRUE)
	{
		std::cout << "Error linking shader" << vertexShader << " to " << fragmentShader << std::endl;
	}
	return program;
}