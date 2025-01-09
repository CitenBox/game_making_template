//
// Created by troll on 12/29/2024.
//

#ifndef SPOTLIGHT_H
#define SPOTLIGHT_H
#include "PointLight.h"


class SpotLight : public PointLight
{
public:
    explicit SpotLight(glm::vec3 rgb = glm::vec3(1.f),
     GLfloat ambientIntensity = 1.f, GLfloat diffuseIntensity = 0.f,
     glm::vec3 position = glm::vec3(0.f),
     GLfloat constant = 1.f, GLfloat linear = 0.f, GLfloat exponent = 0.f,
     glm::vec3 direction = glm::vec3(0,-1,0), GLfloat edge = 0):
      PointLight(rgb, ambientIntensity, diffuseIntensity, position, constant, linear, exponent), direction(direction), edge(edge)
    {
        procEdge = cosf(glm::radians(edge));
    }

    void UseLight(GLint ambientIntensityLocation, GLint ambientColourLocation,
        GLint diffuseIntensityLocation, GLint positionLocation,
        GLint constantLocation, GLint linearLocation, GLint exponentLocation,
        GLint directionLocation, GLint edgeLocation);

    ~SpotLight() = default;

protected:
    glm::vec3 direction = glm::vec3(0);

    GLfloat edge, procEdge;
};



#endif //SPOTLIGHT_H
