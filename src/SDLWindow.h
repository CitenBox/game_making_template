//
// Created by troll on 12/7/2024.
//
#pragma once

#include <iostream>
#include <memory>

#include <SDL.h>
#include <glad/glad.h>

#include "Camera.h"

class SDLWindow
{
public:
    SDLWindow() = default;
    SDLWindow(GLuint windowWidth, GLuint windowHeight);

    int Initialise();

    [[nodiscard]] GLfloat GetWidth() const { return width; }
    [[nodiscard]] GLfloat GetHeight() const { return height; }
    [[nodiscard]] SDL_Window* GetSDLWindow() const { return window; }
    [[nodiscard]] SDL_GLContext GetSDLContext() const { return context; }
    void move(float x, float y);

    void SwapWindow();
    void UpdateWindow();

    void Destroy();
    ~SDLWindow();

protected:
    GLfloat height = 640;
    GLfloat width = 640;
    SDL_Window* window = nullptr;
    SDL_GLContext context = nullptr;

    GLfloat lastX =0.f;
    GLfloat lastY=0.f;
    GLfloat xChange=0.f;
    GLfloat yChange=0.f;

    bool mouseFirstMoved = false;
    bool holdMouseInCenter = false;
};
