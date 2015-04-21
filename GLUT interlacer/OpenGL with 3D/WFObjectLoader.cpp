#include "WFObjectLoader.h"
#include "GraphicsUtil.h"

#include <iostream>
#include <fstream>
#include <string>
#include <stdexcept>
#include <sstream>

using namespace std;

Vertex4 loadVertexLine(std::string line);
Vertex3 loadNormalLine(std::string line);
Vertex2 loadTextureLine(std::string line);

WaveFrontPolygon *WFObjectLoader::loadObjectFile(std::string fileName)
{
	WaveFrontPolygon* poly = new WaveFrontPolygon();
	ifstream file;
	try
	{
		file.open(fileName);
		while (!file.eof())
		{
			//Get each line
			string line;
			if (!getline(file, line)) throw invalid_argument("Couldn't get new line");
			//Split by space and get first element
			stringstream linecpy(line);
			string firstchars;
			getline(linecpy, firstchars, ' ');
			//Pass string to appropriate function
			if (firstchars.compare("v") == 0)
			{
				poly->vertices.push_back(loadVertexLine(linecpy.str()));
			} 
		}
	}
	catch (invalid_argument e)
	{
		file.close();
		delete(poly);
		return NULL;
	}

	return poly;
}

Vertex4 loadVertexLine(std::string line)
{
	Vertex4 vert;
	stringstream vertexVals(line.substr(2, string::npos));
	double vals[] = { 0.0, 0.0, 0.0, 1.0 };
	//Split by space and put into vals array
	int index = 0;
	string val;
	while (!vertexVals.eof())
	{
		getline(vertexVals, val, ' '); 
		vals[index++] = stod(val);
	}	
	vert.x = vals[0];
	vert.y = vals[1];
	vert.z = vals[2];
	vert.w = vals[3];
	return vert;
}