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
WaveFrontPolygonFace loadFace(std::string line);
WaveFrontPolygonFace loadFaceWithVerticesNormals(std::string line);
WaveFrontPolygonFace loadFaceWithVerticesTextures(std::string line);
WaveFrontPolygonFace loadFaceWithVerticesTexturesNormals(std::string line);

WaveFrontPolygon *WFObjectLoader::loadObjectFile(std::string fileName)
{
	WaveFrontPolygon* poly = new WaveFrontPolygon();
	ifstream file;
	try
	{
		file.open(fileName);
		while ( !file.eof() )
		{
			//Get each line
			string line;
			if (!getline(file, line)) 
				break;
			//Split by space and get first element
			stringstream linecpy(line);
			string firstchars;
			getline(linecpy, firstchars, ' ');
			//Pass string to appropriate function
			if ( firstchars.compare("v") == 0 ) //vertices
			{
				poly->vertices.push_back(loadVertexLine(linecpy.str()));
			} else if ( firstchars.compare("vn") == 0 ) //normals
			{
				poly->normals.push_back(loadNormalLine(linecpy.str()));
			} else if ( firstchars.compare("vt") == 0 ) //textures
			{
				poly->textures.push_back(loadTextureLine(linecpy.str()));
			} else if ( firstchars.compare("f") == 0 ) //faces
			{
				if ( line.find("//") != string::npos ) //vertex normals
				{
					poly->faces.push_back(loadFaceWithVerticesNormals(linecpy.str()));
				} else //Assume vertices, normals, textures for now
				{
					poly->faces.push_back(loadFaceWithVerticesTexturesNormals(linecpy.str()));
				}
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

Vertex3 loadNormalLine(std::string line)
{
	Vertex3 vert;
	stringstream vertexVals(line.substr(3, string::npos));
	double vals[] = { 0.0, 0.0, 0.0 };
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
	return vert;
}

Vertex2 loadTextureLine(std::string line)
{
	Vertex2 vert;
	stringstream vertexVals(line.substr(3, string::npos));
	double vals[] = { 0.0, 0.0 };
	int index = 0;
	string val;
	while (!vertexVals.eof())
	{
		getline(vertexVals, val, ' '); 
		vals[index++] = stod(val);
	}
	vert.x = vals[0];
	vert.y = vals[1];
	return vert;
}

WaveFrontPolygonFace loadFace(std::string line)
{
	WaveFrontPolygonFace face;
	return face;
}

WaveFrontPolygonFace loadFaceWithVerticesNormals(std::string line)
{
	WaveFrontPolygonFace face;
	return face;
}

WaveFrontPolygonFace loadFaceWithVerticesTextures(std::string line)
{
	WaveFrontPolygonFace face;
	return face;
}

WaveFrontPolygonFace loadFaceWithVerticesTexturesNormals(std::string line)
{
	WaveFrontPolygonFace face;
	string faceVals(line.substr(2, string::npos));
	//Split by space to get single face
	stringstream faceValsSS(faceVals);
	
	while (!faceValsSS.eof())
	{
		string singleFace;
		getline(faceValsSS, singleFace, ' ');
		stringstream singleFaceSS(singleFace);
		int indices[3];
		for (int i = 0; i < 3; i++) //Split by / and convert to int
		{						
			string ind;
			getline(singleFaceSS, ind, '/');
			indices[i] = stoi(ind);
		}
		face.vertexIndices.push_back(indices[0]); //Put indices into face
		face.normalIndices.push_back(indices[1]);
		face.textureIndices.push_back(indices[2]);
	}
	
	return face;
}