#include "PointLight.h"




void PointLight::UseLight(GLint ambientIntensityLocation, GLint ambientColourLocation,
							GLint diffuseIntensityLocation, GLint positionLocation,
							GLint constantLocation, GLint linearLocation, GLint exponentLocation)
{
	glUniform3f(ambientColourLocation, color.x, color.y, color.z);
	glUniform1f(ambientIntensityLocation, ambientIntensity);
	glUniform1f(diffuseIntensityLocation, diffuseIntensity);

	glUniform3f(positionLocation, position.x, position.y, position.z);
	glUniform1f(constantLocation, constant);
	glUniform1f(linearLocation, linear);
	glUniform1f(exponentLocation, exponent);
}
