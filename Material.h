//
// Created by troll on 12/20/2024.
//

#pragma once


#include <glad/glad.h>

class Material
{
public:
    Material(GLfloat specularIntensity = 0.f, GLfloat shininess = 0.f):
    specularIntensity(specularIntensity), shininess(shininess){}

    void UseMaterial(GLint specularIntensityLocation, GLint shininessLocation) const;

    ~Material() = default;

protected:
    GLfloat specularIntensity;
    GLfloat shininess;
};
