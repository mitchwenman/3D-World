#include "BoundingSphere.h"
#include "GraphicsUtil.h"
#include "libs\glm\gtx\transform.hpp"

TransformableBoundingSphere::TransformableBoundingSphere(WaveFrontPolygon polygon) : BoundingSphere(polygon)
{
	this->worldMatrix = glm::mat4();
	this->worldSpaceCentrePoint = this->centrePoint;
	this->worldRadius = this->radius;
}

void TransformableBoundingSphere::setTransform(std::vector<Transformation *> transforms)
{
	//Reset to identity
	this->worldMatrix = glm::mat4();

	//Create the model view matrix
	for (unsigned int i = 0; i < transforms.size(); i++)
	{
		Transformation *transform = transforms[i];
		switch (transform->type)
		{
		case TRANSLATE:
			{
				glm::vec3 values = glm::vec3(transform->values.x, transform->values.y, 
												transform->values.z);
				worldMatrix = glm::translate(worldMatrix, values);
				break;
			}
		case ROTATE:
			{
				float angle = transform->values.x;
				glm::vec3 values = glm::vec3(transform->values.y, transform->values.z, 
												transform->values.w);
				worldMatrix = glm::rotate(worldMatrix, angle, values);
				break;
			}
		case SCALE:
			{
				//Assuming uniform scaling
				double scaleFactor = transform->values.x;
				this->worldRadius *= scaleFactor;
				break;
			}

			default:
				break;
		}
	}

	//Calculate new centre point
	glm::vec4 newCentre = worldMatrix * glm::vec4(centrePoint, 1.0);
	this->worldSpaceCentrePoint = glm::vec3(newCentre);
}

BoundingSphere TransformableBoundingSphere::transform()
{
	BoundingSphere *bsphere = new BoundingSphere(this->worldSpaceCentrePoint, this->worldRadius);
	return *bsphere;
}