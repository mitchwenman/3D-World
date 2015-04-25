#include "HeightMap.h"


#include "libs\CImg.h"
#include "libs\glm\glm.hpp"

//Load the height map
bool HeightMap::loadFromImage(std::string path)
{
	cimg_library::CImg<unsigned char> image(path.c_str());
	rows = image.width();
	columns = image.height();

	std::vector<std::vector<Vertex3>> vertexData(rows, std::vector<Vertex3>(columns));
	std::vector<std::vector<Vertex2>> textureCoords(rows, std::vector<Vertex2>(columns));

	double textureU = double(columns) / 10; //Instance of texture every 10 by 10 rows/columns
	double textureV = double(rows) / 10;

	//Copy values into vectors - scale to -.5, .5 on X/Z axis, (0, 1) on Y
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < rows; j++)
		{
			double scaleCol = double(j) / double(columns - 1);
			double scaleRow = double(i) / double(rows - 1);
			double vertexHeight = image(i, j, 0, 0, 0) / 255.0;
			Vertex3 vertex = { -0.5 + scaleCol, vertexHeight, -0.5 + scaleRow };
			Vertex2 texture = { textureU * scaleCol, textureV * scaleRow };

			vertexData[i][j] = vertex;
			textureCoords[i][j] = texture;
		}
	}
	//Calculate normals
	
	std::vector< std::vector<glm::vec3> > vNormals[3];
	vNormals[0] = std::vector< std::vector<glm::vec3> >(rows - 1, std::vector<glm::vec3>(columns - 1));
	vNormals[1] = std::vector< std::vector<glm::vec3> >(rows - 1, std::vector<glm::vec3>(columns - 1));
	vNormals[2] = std::vector< std::vector<glm::vec3> >(rows - 1, std::vector<glm::vec3>(columns - 1));
	
	return true;
}