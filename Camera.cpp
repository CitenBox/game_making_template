//
// Created by troll on 12/11/2024.
//

#include "Camera.h"
#include <SDL_mouse.h>
#include <cmath>
#include <iostream>
#include <map>
#include <SDL_events.h>
#include <valarray>
#include <glad/glad.h>
#include <glm/ext/scalar_constants.hpp>
#include <numbers>
#include <glm/geometric.hpp>
#include <glm/ext/matrix_transform.hpp>

void Camera::LockCamera()
{
    if (pitch > 90)
        pitch = 90;
    if (pitch < -90)
        pitch = -90;

    if (yaw < 0)
        yaw += 360;
    if (yaw > 360)
        yaw -= 360;
}

void Camera::MoveCamera(float direction)
{
    const float rad = (yaw+direction) * glm::pi<float>()/180.f;
    location.x -= glm::sin(rad)*moveSpeed;
    location.z -= glm::cos(rad)*moveSpeed;
}

void Camera::MoveCameraUp(float direction)
{
    const float rad = (pitch + direction) * glm::pi<float>()/180.f;
    location.y += glm::sin(rad)*moveSpeed;
}

void Camera::Init()
{
    UpdateCamera();
}

Camera::Camera(glm::vec3 startLocation, glm::vec3 worldUp, float startPitch, float startYaw, float moveSpeed, float turnSpeed) :
   location(startLocation), worldUp(worldUp), pitch(startPitch), yaw(startYaw), moveSpeed(moveSpeed), turnSpeed(turnSpeed)
{
    Init();
}


void Camera::Control(float deltaTime)
{
    SDL_Event event;
    while (SDL_PollEvent(&event))
    {
        if (event.type == SDL_MOUSEMOTION)
        {
            MouseControl(event.motion.xrel, event.motion.yrel, deltaTime);
        }
    }

    const uint8_t* keyboardState = SDL_GetKeyboardState(nullptr);

    if (keyboardState[SDL_SCANCODE_W])
    {
        location += front * moveSpeed * deltaTime;
    }
    if (keyboardState[SDL_SCANCODE_S])
    {
        location -= front * moveSpeed * deltaTime;
    }
    if (keyboardState[SDL_SCANCODE_A])
    {
        location -= right * moveSpeed * deltaTime;
    }
    if (keyboardState[SDL_SCANCODE_D])
    {
        location += right * moveSpeed * deltaTime;
    }
}

void Camera::MouseControl(float xChange, float yChange, float deltaTime)
{
    xChange *= turnSpeed * deltaTime;
    yChange *= turnSpeed * deltaTime;

    yaw += xChange;
    pitch -= yChange;

    if (pitch > 89.f)
    {
        pitch = 89.f;
    }

    if (pitch < -89.f)
    {
        pitch = -89.f;
    }
    UpdateCamera();
}


void Camera::UpdateCamera()
{
    front.x = glm::cos(glm::radians(yaw)) * glm::cos(glm::radians(pitch));
    front.y = glm::sin(glm::radians(pitch));
    front.z =  glm::sin(glm::radians(yaw)) * glm::cos(glm::radians(pitch));
    front = normalize(front);

    right = normalize(cross(front, worldUp));
    up = normalize(cross(right, front));
}

glm::mat4 Camera::CalculateViewMatrix() const
{
    return glm::lookAt(location, location + front, up);
}

glm::vec3 Camera::getVector() const
{
    return
    {
    -glm::cos(pitch*M_PI/180.0)*glm::sin(yaw*M_PI/180.0),
    glm::sin(pitch*M_PI/180.0),
    -glm::cos(pitch*M_PI/180.0)*glm::cos(yaw*M_PI/180.0)
    };
}

void Camera::LookAt(float pitch, float yaw)
{
    this->pitch = pitch;
    this->yaw = yaw;
}



