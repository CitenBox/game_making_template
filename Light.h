//
// Created by troll on 12/16/2024.
//

#ifndef LIGHT_H
#define LIGHT_H

#include <glm/glm.hpp>
#include <glad/glad.h>

class Light
{
public:

    explicit Light(const glm::vec3 color = glm::vec3(1.f), GLfloat ambientIntensity = 1.f, GLfloat diffuseIntensity = 0.f):
    color(color), ambientIntensity(ambientIntensity), diffuseIntensity(diffuseIntensity){}

    ~Light() = default;

protected:
    glm::vec3 color = glm::vec3(1.f);
    GLfloat ambientIntensity;
    GLfloat diffuseIntensity;
};



#endif //LIGHT_H
