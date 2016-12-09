///////////////////////////////////////////////////////////////////////////////////
// Filename: MazeReader.cpp
// Author: Mitch Wenman
// Date Modified: 20/05/2015
// Description: Loads a maze from file.
///////////////////////////////////////////////////////////////////////////////////

// ============== INCLUDES =================//
#include "MazeReader.h"

#include <fstream>
#include <stdexcept>
#include <sstream>

using namespace std;

// ============== FUNCTIONS =================//
std::vector<std::vector<bool>> MazeReader::readFromFile(std::string path)
{
	std::vector< std::vector<bool> > walls;
	ifstream file;
	file.open(path);
	if (!file.is_open())
		return walls;

	//Read each line
	while (!file.eof())
	{
		string line;
		getline(file, line);
		stringstream row(line);
		std::vector<bool> wallRow;
		while (!row.eof())
		{
			
			string character; //Either '1' or '0'
			getline(row, character, ' ');
			int isWall = stoi(character);
			if (isWall == 1)
			{
				wallRow.push_back(true);
			} else if (isWall == 0)
			{
				wallRow.push_back(false);
			}			
		}
		walls.push_back(wallRow);
	}
	file.close();
	return walls;
}