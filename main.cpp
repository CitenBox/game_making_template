#include <algorithm>
#include <SDL.h>
#include <glad/glad.h>
#include <iostream>
#include <string>
#include <cmath>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <fstream>
#include <vector>
#include "Mesh.h"
#include "Shader.h"
#include "SDLWindow.h"

using namespace std;

// Globals

SDLWindow mainWindow;
std::vector<Mesh*> meshList;
std::vector<Shader*> shaderList;

glm::mat4 projection;

bool gQuit = false; //if true we quit.

void CleanUp();
void CreateObjects();
void CreateShaders();

void GetOpenGLVersionInfo()
{
    std::cout << "Vendor: " << glGetString(GL_VENDOR) << '\n';
    std::cout << "Renderer: " << glGetString(GL_RENDERER) << '\n';
    std::cout << "Version: " << glGetString(GL_VERSION) << '\n';
    std::cout << "Shading Language: " << glGetString(GL_SHADING_LANGUAGE_VERSION) << '\n';
}

void InitializeProgram()
{
    mainWindow = SDLWindow(800, 600);
    if (mainWindow.Initialise() != 0)
    {
        cout << "SDLWindow initialisation failed!\n";
        CleanUp();
    }
    
    GetOpenGLVersionInfo();

    CreateObjects();
    CreateShaders();

    projection = glm::perspective(45.f, (GLfloat)mainWindow.GetWidth()/mainWindow.GetHeight(), 0.1f, 100.f);
}

SDL_MouseMotionEvent me = SDL_MouseMotionEvent();
void Input()
{
    SDL_Event e;

    while(SDL_PollEvent(&e) != 0)
    {
        if(e.type == SDL_QUIT)
        {
            std::cout << "Quitting\n";
            gQuit = true;
        }

        if (e.type == SDL_KEYDOWN)
        {
            if (e.key.keysym.scancode == SDL_SCANCODE_W)
            {
                mainWindow.move(10);
            }
        }
    }
}

void PreDraw()
{
    glClearColor(0.f, 0.f, 0.f ,1.f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Draw()
{
    GLint uniformProjection = 0, uniformModel = 0;

    if (shaderList[0])
    {
        shaderList[0]->UseShader();
        uniformModel = shaderList[0]->GetModelLocation();
        uniformProjection = shaderList[0]->GetProjectionLocation();
    }

    auto model = glm::mat4(1.0f);

    model = translate(model, glm::vec3(0.f, 0.f, -2.5f));
    model = scale(model, glm::vec3(0.4f, 0.4f, 1.0f));
    glUniformMatrix4fv(uniformModel, 1, GL_FALSE, value_ptr(model));
    glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, value_ptr(projection));
    if (meshList[0] != nullptr)
    {
        meshList[0]->RenderMesh();
    }

    model = glm::mat4(1.0f);
    model = translate(model, glm::vec3(0.f, 1, 2.5f));
    model = scale(model, glm::vec3(0.4f, 0.4f, 1.0f));
    glUniformMatrix4fv(uniformModel, 1, GL_FALSE, value_ptr(model));
    if (meshList[1] != nullptr)
    {
        meshList[1]->RenderMesh();
    }

    glUseProgram(0);
}

void CreateObjects()
{
    unsigned int indices[]
    {
        0, 3, 1,
        1, 3, 2,
        2, 3, 0,
        0, 1, 2,
    };
    
    GLfloat vertices[]
    {
        -1.f, -1.f, 0.f,
        0.f, -1.f, 1.f,
        1.f, -1.f, 0.f,
        0.f, 1.f, 0.f,
    };

    auto *obj1 = new Mesh();
    obj1->CreateMesh(vertices, indices, 12, 12);
    meshList.push_back(obj1);

    auto *obj2 = new Mesh();
    obj2->CreateMesh(vertices, indices, 12, 12);
    meshList.push_back(obj2);
}

void MainLoop()
{
    while(!gQuit)
    {
        Input();
        PreDraw();
        Draw();
        
        mainWindow.SwapWindow();
    }
}

void CleanUp()
{
    mainWindow.Destroy();
    SDL_Quit();
}

void CreateShaders()
{
    auto* shader1 = new Shader();
    shader1->CreateFromFile((std::string)SHADER_DIR + "shader.vert", (std::string)SHADER_DIR + "shader.frag");
    shaderList.push_back(shader1);
}

int main(int argc, char* argv[])
{
    InitializeProgram();

    MainLoop();

    CleanUp();

    return 0;
}