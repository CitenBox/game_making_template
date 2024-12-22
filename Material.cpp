//
// Created by troll on 12/20/2024.
//

#include "Material.h"

void Material::UseMaterial(GLint specularIntensityLocation, GLint shininessLocation) const
{
    glUniform1f(specularIntensityLocation, specularIntensity);
    glUniform1f(shininessLocation, shininess);
}
