#pragma once
#include "Light.h"

class DirectionalLight : public Light
{
public:
	explicit DirectionalLight(const glm::vec3 color = glm::vec3(1.f),
	GLfloat ambientIntensity = 1.f,
	GLfloat diffuseIntensity = 0.f,
	glm::vec3 direction = glm::vec3(0.f,-1.f,0.f))
	:
	Light(color, ambientIntensity, diffuseIntensity), direction(direction){};


	void UseLight(GLint ambientIntensityLocation, GLint ambientColorLocation,
	GLint diffuseIntensityLocation, GLint directionLocation);

	~DirectionalLight() = default;

protected:
	glm::vec3 direction;
};

inline void DirectionalLight::UseLight(GLint ambientIntensityLocation, GLint ambientColorLocation,
	GLint diffuseIntensityLocation,
	GLint directionLocation)
{
	glUniform3f(ambientColorLocation, color.x, color.y, color.z);
	glUniform1f(ambientIntensityLocation, ambientIntensity);

	glUniform3f(directionLocation, direction.x, direction.y, direction.z);
	glUniform1f(diffuseIntensityLocation, diffuseIntensity);
}

