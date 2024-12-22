#include "PointLight.h"




void PointLight::UseLight(GLfloat ambientIntensityLocation, GLfloat ambientColourLocation, 
							GLfloat diffuseIntensityLocation, GLfloat positionLocation, 
							GLfloat constantLocation, GLfloat linearLocation, GLfloat exponentLocation)
{
	glUniform3f(ambientColourLocation, color.x, color.y, color.z);
	glUniform1f(ambientIntensityLocation, ambientIntensity);
	glUniform1f(diffuseIntensityLocation, diffuseIntensity);

	glUniform3f(positionLocation, location.x, location.y, location.z);
	glUniform1f(constantLocation, constant);
	glUniform1f(linearLocation, linear);
	glUniform1f(exponentLocation, exponent);
}
