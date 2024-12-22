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

    explicit Light(const glm::vec3 color = glm::vec3(1.f), GLfloat ambientIntensity = 1.f, GLfloat diffuseIntensity = 0.f, glm::vec3 direction = glm::vec3(0.f,-1.f,0.f)):
    color(color), ambientIntensity(ambientIntensity), direction(direction), diffuseIntensity(diffuseIntensity){}

    void UseLight(GLint ambientIntensityLocation, GLint ambientColorLocation,
        GLint diffuseIntensityLocation, GLint directionLocation);

    ~Light() = default;

protected:
    glm::vec3 color = glm::vec3(1.f);
    GLfloat ambientIntensity;

    glm::vec3 direction;
    GLfloat diffuseIntensity;
};



#endif //LIGHT_H
