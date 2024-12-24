#pragma once
#include "Light.h"

class PointLight :
	public Light
{
public:

	explicit PointLight(glm::vec3 rgb = glm::vec3(1.f),
		GLfloat ambientIntensity = 1.f, GLfloat diffuseIntensity = 0.f,
		glm::vec3 position = glm::vec3(0.f),
		GLfloat constant = 1.f, GLfloat linear = 0.f, GLfloat exponent = 0.f):
 		Light(rgb, ambientIntensity, diffuseIntensity), position(position), constant(constant),
  		linear(linear), exponent(exponent){}

	void UseLight(GLint ambientIntensityLocation, GLint ambientColourLocation,
		GLint diffuseIntensityLocation, GLint positionLocation,
		GLint constantLocation, GLint linearLocation, GLint exponentLocation);

	~PointLight() = default;

protected:
	glm::vec3 position;

	GLfloat constant, linear, exponent;
};

