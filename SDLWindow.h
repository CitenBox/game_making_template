//
// Created by troll on 12/7/2024.
//
#pragma once

#include <iostream>
#include <SDL.h>
#include <glad/glad.h>

class SDLWindow
{
public:
    SDLWindow();
    SDLWindow(GLuint windowWidth, GLuint windowHeight);

    int Initialise();

    [[nodiscard]] GLfloat GetWidth() const { return width; }
    [[nodiscard]] GLfloat GetHeight() const { return height; }
    [[nodiscard]] SDL_Window* GetSDLWindow() const { return window; }
    [[nodiscard]] SDL_GLContext GetSDLContext() const { return context; }
    void move(float x, float y);

    void SwapWindow() const { SDL_GL_SwapWindow(window); }

    void Destroy();
    ~SDLWindow();

protected:
    GLfloat height = 640;
    GLfloat width = 640;
    SDL_Window* window = nullptr;
    SDL_GLContext context = nullptr;

    bool keys[1024];
};