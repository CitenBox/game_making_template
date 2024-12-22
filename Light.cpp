//
// Created by troll on 12/16/2024.
//

#include "Light.h"

void Light::UseLight(GLint ambientIntensityLocation, GLint ambientColorLocation,
    GLint diffuseIntensityLocation, GLint directionLocation)
{
    glUniform3f(ambientColorLocation, color.x, color.y, color.z);
    glUniform1f(ambientIntensityLocation, ambientIntensity);

    glUniform3f(directionLocation, direction.x, direction.y, direction.z);
    glUniform1f(diffuseIntensityLocation, diffuseIntensity);

}
