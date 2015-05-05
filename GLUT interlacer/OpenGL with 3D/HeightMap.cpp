#include "HeightMap.h"
#include "libs\CImg.h"
#include "libs\glm\glm.hpp"
#include "GraphicsUtil.h"


/*  Heavily derived from this Heightmap tutorial:
	http://www.mbsoftworks.sk/index.php?page=tutorials&series=1&tutorial=24
*/


//Load the height map
void HeightMap::loadFromImage(std::string path)
{
	cimg_library::CImg<unsigned char> image(path.c_str());
	rows = image.width();
	columns = image.height();

	//2 dimensional array - rows X columns, each element is one column
	vertexData = std::vector<std::vector<Vertex3>>(rows, std::vector<Vertex3>(columns));
	textureCoords = std::vector<std::vector<Vertex2>>(rows, std::vector<Vertex2>(columns));

	//Copy values into vectors - scale to 0, 1 on Y axis and 1/5 size of image
	double xoffset = -7.5;
	double zoffset = -7.5;
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < columns; j++)
		{
			//Scale vertices
			double xScale = double(j) / (.05 * double(columns - 1));
			double zScale = double(i) / (.05 * double(rows - 1));
			//Get pixel heigh value
			double vertexHeight = image(i, j, 0, 0, 0) / 64.; //Just use Red values if RGB
			Vertex3 vertex = { xoffset + xScale, vertexHeight, zoffset + zScale }; 
			//Create repeated texture every 20x20 pixels
			Vertex2 texture = { rows / 20. * (i / (double)rows), columns / 20. * (j / double(columns)) };

			vertexData[i][j] = vertex;
			textureCoords[i][j] = texture;
		}
	}
	this->calculateNormals();
	//Create vertex data for easy rendering
	vList.reserve(rows * columns * 3);
	nList.reserve(rows * columns * 3);
	tList.reserve(rows * columns * 2);
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < columns; j++)
		{
			vList.push_back(vertexData[i][j].x);
			vList.push_back(vertexData[i][j].y);
			vList.push_back(vertexData[i][j].z);
			nList.push_back(normals[i][j].x);
			nList.push_back(normals[i][j].y);
			nList.push_back(normals[i][j].z);
			tList.push_back(textureCoords[i][j].x);
			tList.push_back(textureCoords[i][j].y);
		}
	}
	//Use restart index so we can use triangle strips
	//row * columns will be out of bounds, therefore 
	//never used in the array, so we can use it as the restart value
	int restartIndex = rows * columns;
	for (int i = 0; i < rows - 1; i++)
	{
		for (int j = 0; j < columns; j++)
		{
			indices.push_back(i * columns + j);
			indices.push_back((i + 1) * columns + j);
		}
		indices.push_back(restartIndex);
	}	
}

void HeightMap::render()
{
	glEnableClientState(GL_VERTEX_ARRAY);
	glVertexPointer(3, GL_DOUBLE, 0, vList.data());
	glEnableClientState(GL_NORMAL_ARRAY);
	glNormalPointer(GL_DOUBLE, 0, nList.data());	
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);
	glTexCoordPointer(2, GL_DOUBLE, 0, tList.data());
	glPrimitiveRestartIndex(rows * columns);
	glEnable(GL_PRIMITIVE_RESTART);
	glDrawElements(GL_TRIANGLE_STRIP, indices.size(), GL_UNSIGNED_INT, indices.data());
	glDisable(GL_PRIMITIVE_RESTART);
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);
	glDisableClientState(GL_NORMAL_ARRAY);
	glDisableClientState(GL_VERTEX_ARRAY);
}

void HeightMap::calculateNormals()
{
	//Calculate triangle surface normals
	//3D array: Rows x Columns x (2 triangles per quad)
	std::vector< std::vector<glm::vec3> > vNormals[2];
	vNormals[0] = std::vector< std::vector<glm::vec3> >(rows - 1, std::vector<glm::vec3>(columns - 1));
	vNormals[1] = std::vector< std::vector<glm::vec3> >(rows - 1, std::vector<glm::vec3>(columns - 1));
	//Get 2 normals for each adjacent quad containing 2 triangles
	for (int i = 0; i < rows - 1; i++)
	{
		for (int j = 0; j < columns - 1; j++)
		{
			glm::vec3 tri0[] = 
			{
				GraphicsUtil::vertex3ToGLMVec3(vertexData[i][j]),
				GraphicsUtil::vertex3ToGLMVec3(vertexData[i + 1][j]),
				GraphicsUtil::vertex3ToGLMVec3(vertexData[i][j + 1])
			};
			glm::vec3 tri1[] = 
			{
				GraphicsUtil::vertex3ToGLMVec3(vertexData[i][j + 1]),
				GraphicsUtil::vertex3ToGLMVec3(vertexData[i + 1][j]),
				GraphicsUtil::vertex3ToGLMVec3(vertexData[i + 1][j + 1])
			};
			glm::vec3 triNorm0 = glm::cross(tri0[0] - tri0[1], tri0[1] - tri0[2]);
			glm::vec3 triNorm1 = glm::cross(tri1[0] - tri1[1], tri1[1] - tri1[2]);
			vNormals[0][i][j] = glm::normalize(triNorm0);
			vNormals[1][i][j] = glm::normalize(triNorm1);
		}
	}
	//Add and normalise from 1 top left, 2 top right, 2 bottom left, 1 bottom right
	/*
	---------
	|0/1| / |
	----V----
	| / | / |
	---------
	*/
	normals = std::vector <std::vector<Vertex3 > >(rows, std::vector<Vertex3>(columns));
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < columns; j++)
		{
			glm::vec3 finalNorm = glm::vec3(0.0, 0.0, 0.0);
			//Top left
			if (j != 0 && i != 0)
			{
				finalNorm += vNormals[1][i - 1][j - 1];
			}
			//Top right
			if (i != 0 && j != columns - 1) 
			{
				finalNorm += vNormals[0][i - 1][j];
				finalNorm += vNormals[1][i - 1][j];
			}
			//bottom right
			if (i != rows - 1 && j != columns - 1)
			{
				finalNorm += vNormals[0][i][j];
			}
			//bottom left
			if (i != rows - 1 && j != 0)
			{
				finalNorm += vNormals[0][i][j - 1];
				finalNorm += vNormals[1][i][j - 1];
			}
				
			//Average out value
			finalNorm = glm::normalize(finalNorm);
			normals[i][j] = GraphicsUtil::GLMVec3ToVertex3(finalNorm);
		}
	} 
}