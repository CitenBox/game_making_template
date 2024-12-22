#pragma once
#include "Light.h"

class PointLight :
	public Light
{
public:

	explicit PointLight(glm::vec3 rgb = glm::vec3(1.f),
		GLfloat ambientIntensity = 1.f, GLfloat diffuseIntensity = 0.f,
		glm::vec3 location = glm::vec3(0.f),
		GLfloat constant = 1.f, GLfloat linear = 0.f, GLfloat exponent = 0.f):
 		Light(rgb, ambientIntensity, diffuseIntensity), location(location), constant(constant),
  		linear(linear), exponent(exponent){}

	void UseLight(GLfloat ambientIntensityLocation, GLfloat ambientColourLocation,
		GLfloat diffuseIntensityLocation, GLfloat positionLocation,
		GLfloat constantLocation, GLfloat linearLocation, GLfloat exponentLocation);

	~PointLight() = default;

protected:
	glm::vec3 location;

	GLfloat constant, linear, exponent;
};

