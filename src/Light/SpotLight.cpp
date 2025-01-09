//
// Created by troll on 12/29/2024.
//

#include "SpotLight.h"

void SpotLight::UseLight
(
    GLint ambientIntensityLocation, GLint ambientColourLocation, GLint diffuseIntensityLocation, GLint positionLocation,
    GLint constantLocation, GLint linearLocation, GLint exponentLocation, GLint directionLocation, GLint edgeLocation
)
{
    glUniform3f(ambientColourLocation, color.r, color.g, color.b);
    glUniform1f(ambientIntensityLocation, ambientIntensity);
    glUniform1f(diffuseIntensityLocation, diffuseIntensity);

    glUniform3f(positionLocation, position.x, position.y, position.z);
    glUniform1f(constantLocation, constant);
    glUniform1f(linearLocation, linear);
    glUniform1f(exponentLocation, exponent);

    glUniform3f(directionLocation, direction.x, direction.y, direction.z);
    glUniform1f(edgeLocation, procEdge);
}
