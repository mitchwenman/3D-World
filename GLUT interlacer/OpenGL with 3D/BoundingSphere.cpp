#include "BoundingSphere.h"
#include <cmath>

BoundingSphere::BoundingSphere(WaveFrontPolygon polygon)
{
	//Group together position data so it's easier to use for calculations
	std::vector<float> positionData = polygon.vertices;
	std::vector<glm::vec3> groupedVertices(positionData.size() / 3);
	for (unsigned int i = 0; i < positionData.size(); i += 3)
	{
		glm::vec3 vertex = glm::vec3(positionData[i], positionData[i + 1], positionData[i + 2]);
		groupedVertices.push_back(vertex);
	}

	//Create bounding box to find centre point
	double minZ, maxZ, minY, maxY, minX, maxX;
	minZ = maxZ = groupedVertices[0].z;
	minY = maxY = groupedVertices[0].y;
	minX = maxX = groupedVertices[0].x;
	glm::vec3 minXCoord, maxXCoord, minYCoord, maxYCoord, minZCoord, maxZCoord;
	for (unsigned int i = 1; i < groupedVertices.size(); i++)
	{
		glm::vec3 vert = groupedVertices[i];
		if (vert.x > maxX)
		{
			maxX = vert.x;
			maxXCoord = glm::vec3(vert.x, vert.y, vert.z);
		}			
		else if (vert.x < minX)
		{
			minX = vert.x;
			minXCoord = glm::vec3(vert.x, vert.y, vert.z);
		}

		if (vert.y > maxY)
		{
			maxY = vert.y;
			maxYCoord = glm::vec3(vert.x, vert.y, vert.z);
		}
		else if (vert.y < minY) 
		{
			minY = vert.y;
			minYCoord = glm::vec3(vert.x, vert.y, vert.z);
		}

		if (vert.z > maxZ)
		{
			maxZ = vert.z;
			maxZCoord = glm::vec3(vert.x, vert.y, vert.z);
		}
		else if (vert.z < minZ) 
		{
			minZ = vert.z;
			minZCoord = glm::vec3(vert.x, vert.y, vert.z);
		}
	}
	
	double xSpan = maxX - minX;
	double ySpan = maxY - minY;
	double zSpan = maxZ - minZ;
	this->centrePoint = glm::vec3(xSpan / 2 + minX, ySpan / 2 + minY, zSpan / 2 + minZ);

	//Radius is greatest distance between centre point and min/max coords
	double maxXCoordDist = std::max(glm::distance(maxXCoord, centrePoint), glm::distance(minXCoord, centrePoint));
	double maxYCoordDist = std::max(glm::distance(maxYCoord, centrePoint), glm::distance(minYCoord, centrePoint));
	double maxZCoordDist = std::max(glm::distance(maxZCoord, centrePoint), glm::distance(minZCoord, centrePoint));
	this->radius = std::max((maxXCoordDist, maxYCoordDist), maxZCoordDist);
}