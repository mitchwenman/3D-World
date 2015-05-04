#pragma once

#include <vector>
#include <string>

namespace MazeReader
{
	//! Reads a maze file at the given path and constructs
	//! a 2D vector representing it.
	//! @param path The path to the file.
	//! @returns A 2D vector of booleans, where true represents a wall at position i,j.
	std::vector<std::vector<bool>> readFromFile(std::string path);
};