//
// Created by troll on 12/11/2024.
//
#pragma once

#include <glm/fwd.hpp>
#include <glm/vec3.hpp>

class Camera {
public:

    explicit Camera(
        glm::vec3 startLocation = glm::vec3(0.f),
        glm::vec3 worldUp = glm::vec3(0.f),
        float startPitch = 0.0f,
        float startYaw = 0.0f,
        float moveSpeed = 0.2f,
        float turnSpeed = 0.2f
        );
    ~Camera() = default;

    void Control(float deltaTime);
    void MouseControl(float xChange, float yChange, float deltaTime);

    void UpdateCamera();

    [[nodiscard]] glm::vec3 getCameraPosition() const { return location; }

    [[nodiscard]] glm::mat4 CalculateViewMatrix() const;

    //converts coordinate system from spherical to cartesian.
    [[nodiscard]] glm::vec3 getVector() const;

    [[nodiscard]] const glm::vec3& getLocation() const { return location; }
    [[nodiscard]] float getPitch() const { return pitch; }
    [[nodiscard]] float getYaw() const { return yaw; }
    [[nodiscard]] float getMoveSpeed() const { return moveSpeed; }
    [[nodiscard]] float getTurnSpeed() const { return turnSpeed; }
    [[nodiscard]] bool isMouseInWindow() const { return bMouseInWindow; }

    void setLocation(const glm::vec3& location) { this->location = location; }
    void setMoveSpeed(const float moveSpeed) { this->moveSpeed = moveSpeed; }
    void setMouseSpeed(const float mouseSpeed) { this->turnSpeed = mouseSpeed; }
    void setIsMouseInWindow(const bool bIsInWindow) { bMouseInWindow = bIsInWindow; }
    void LookAt(float pitch, float yaw);

protected:

    glm::vec3 location = glm::vec3(0.f);
    glm::vec3 front = glm::vec3(0.f);
    glm::vec3 up = glm::vec3(0.f);
    glm::vec3 right = glm::vec3(0.f);
    glm::vec3 worldUp = glm::vec3(0.f);

    float pitch = 0.f, yaw = 0.f;
    float moveSpeed = 0.2f;
    float turnSpeed = 0.2f;

    struct SDL_Window* window = nullptr;

    bool bMouseInWindow = false;
    void LockCamera();
    void MoveCamera(float direction);
    void MoveCameraUp(float direction);
    void Init();

};


