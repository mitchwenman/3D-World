#include "HeightMap.h"


#include "libs\CImg.h"
#include "libs\glm\glm.hpp"
#include "GraphicsUtil.h"

//Load the height map
bool HeightMap::loadFromImage(std::string path)
{
	cimg_library::CImg<unsigned char> image(path.c_str());
	rows = image.width();
	columns = image.height();

	vertexData = std::vector<std::vector<Vertex3>>(rows, std::vector<Vertex3>(columns));
	textureCoords = std::vector<std::vector<Vertex2>>(rows, std::vector<Vertex2>(columns));

	double textureU = double(columns) / 10; //Instance of texture every 10 by 10 rows/columns
	double textureV = double(rows) / 10;

	//Copy values into vectors - scale to 0, 1 on Y axis and 1/5 size of image
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < columns; j++)
		{
			double scaleCol = double(j) / (.2 * double(columns - 1));
			double scaleRow = double(i) / (.2 * double(rows - 1));
			double vertexHeight = image(i, j, 0, 0, 0) / 255.0;
			Vertex3 vertex = { -.5 + scaleCol, vertexHeight, -.5 + scaleRow };
			Vertex2 texture = { textureU * scaleCol, textureV * scaleRow };

			vertexData[i][j] = vertex;
			textureCoords[i][j] = texture;
		}
	}
	//Calculate normals	
	std::vector< std::vector<glm::vec3> > vNormals[2];
	vNormals[0] = std::vector< std::vector<glm::vec3> >(rows - 1, std::vector<glm::vec3>(columns - 1));
	vNormals[1] = std::vector< std::vector<glm::vec3> >(rows - 1, std::vector<glm::vec3>(columns - 1));
	//Get normal for each adjacent quad containing 2 triangles
	for (int i = 0; i < rows - 1; i++)
	{
		for (int j = 0; j < columns - 1; j++)
		{
			glm::vec3 tri0[] = 
			{
				GraphicsUtil::vertex3ToGLMVec3(vertexData[i][j]),
				GraphicsUtil::vertex3ToGLMVec3(vertexData[i + 1][j]),
				GraphicsUtil::vertex3ToGLMVec3(vertexData[i + 1][j + 1])
			};
			glm::vec3 tri1[] = 
			{
				GraphicsUtil::vertex3ToGLMVec3(vertexData[i + 1][j + 1]),
				GraphicsUtil::vertex3ToGLMVec3(vertexData[i][j + 1]),
				GraphicsUtil::vertex3ToGLMVec3(vertexData[i][j])
			};
			glm::vec3 triNorm0 = glm::cross(tri0[0] - tri0[1], tri0[1] - tri0[2]);
			glm::vec3 triNorm1 = glm::cross(tri1[0] - tri1[1], tri1[1] - tri1[2]);
			vNormals[0][i][j] = glm::normalize(triNorm0);
			vNormals[1][i][j] = glm::normalize(triNorm1);
		}
	}
	//Add and normalise from 2 top left triangles, 1 top right, 2 bottom left, 1 right
	normals = std::vector <std::vector<Vertex3 > >(rows, std::vector<Vertex3>(columns));
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < columns; j++)
		{
			glm::vec3 finalNorm = glm::vec3(0.0, 0.0, 0.0);
			//Top left
			if (j != 0 && i != 0)
				for (int k = 0; k < 2; k++) finalNorm += vNormals[k][i - 1][j - 1];
			//Top right
			if (i != 0 && j != columns - 1) finalNorm += vNormals[0][i - 1][j];
			//bottom right
			if (i != rows - 1 && j != columns - 1)
				for (int k = 0; k < 2; k++) finalNorm += vNormals[0][i][j];
			//bottom left
			if (i != rows - 1 && j != 0)
				finalNorm += vNormals[1][i][j - 1];
			//Average out value
			finalNorm = glm::normalize(finalNorm);
			normals[i][j] = GraphicsUtil::GLMVec3ToVertex3(finalNorm);
		}
	}
	indices.reserve((rows - 1) * (columns - 1) * 6); //Each row gives 6 indices for 2 triangles
	//Create indices vect for indexed array
	for (int i = 0; i < rows - 1; i++)
	{
		for (int j = 0; j < columns - 1; j++)
		{
			int v = i + j * columns;
			indices.push_back(v + columns);
			indices.push_back(v);
			indices.push_back(v + columns + 1);
			indices.push_back(v + columns + 1);
			indices.push_back(v);
			indices.push_back(v + 1);
		}
	}
	//Add data to list for quick drawing
	vList.reserve(3 * rows * columns);
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < columns; j++)
		{
			vList.push_back(vertexData[i][j].x);
			vList.push_back(vertexData[i][j].y);
			vList.push_back(vertexData[i][j].z);
		}
	}
	return true;
}

void HeightMap::render()
{
	glEnableClientState(GL_VERTEX_ARRAY);

	glVertexPointer(3, GL_DOUBLE, 0, vList.data());

	glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_SHORT, indices.data());
	glDisableClientState(GL_VERTEX_ARRAY);
}