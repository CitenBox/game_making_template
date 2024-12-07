//
// Created by troll on 12/7/2024.
//

#include "SDLWindow.h"

SDLWindow::SDLWindow()
{
}

SDLWindow::SDLWindow(GLuint windowWidth, GLuint windowHeight)
{
    width = windowWidth;
    height = windowHeight;

    for (bool& key : keys)
    {
        key = false;
    }
}

int SDLWindow::Initialise()
{
    if(SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        std::cout << "SDL2 could not initialize video subsystem\n";
        exit(1);
    }

    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);

    SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS, SDL_GL_CONTEXT_FORWARD_COMPATIBLE_FLAG);

    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);

    window = SDL_CreateWindow("OpenGL Window", 0,0, width, height, SDL_WINDOW_OPENGL);

    if(window == nullptr)
    {
        std::cout << "SDL2 could not create window\n";
        return 1;
    }

    context = SDL_GL_CreateContext(window);

    if(context == nullptr)
    {
        std::cout << "OpenGL context not available\n";
        return 1;
    }

    //glewExperimental = GL_TRUE;

    if (!gladLoadGLLoader(SDL_GL_GetProcAddress)) {
        std::cerr << "Failed to initialize GLAD" << std::endl;
        SDL_GL_DeleteContext(context);
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }

    glEnable(GL_DEPTH_TEST);

    glViewport(0,0, width, height);

    return 0;
}

void SDLWindow::move(float x, float y)
{
}

void SDLWindow::Destroy()
{
    SDL_GL_DeleteContext(context);
    SDL_DestroyWindow(window);
}

SDLWindow::~SDLWindow()
{
    Destroy();
}
