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
#include "Camera.h"
#include "Texture.h"
#include "Material.h"
#include "ErrorReportingGPU.h"
#include "Light/DirectionalLight.h"
#include "CommonValues.h"
#include "Light/PointLight.h"
#include "Light/SpotLight.h"


using namespace std;

// Globals

SDLWindow mainWindow;
Camera camera;

std::vector<Mesh*> meshList;
std::vector<Shader*> shaderList;

Texture brickTexture;
Texture dirtTexture;
Texture plainTexture;

Material shinyMaterial;
Material dullMaterial;

DirectionalLight mainLight;
PointLight pointLights[MAX_POINT_LIGHTS];
SpotLight spotLights[MAX_SPOT_LIGHTS];
unsigned pointLightCount = 0;
unsigned spotLightCount = 0;

double deltaTime = 0.0f;
uint64_t lastTime = 0.0f;
uint64_t now = SDL_GetPerformanceCounter();

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
    mainWindow = SDLWindow(1366, 1024);
    if (mainWindow.Initialise() != 0)
    {
        cout << "SDLWindow initialisation failed!\n";
        CleanUp();
    }
    GetOpenGLVersionInfo();

    enableReportGlErrors();

    CreateObjects();
    CreateShaders();

    camera = Camera(glm::vec3(0), glm::vec3(0,1,0), 0, 0, 0.005f, 0.02f);

    brickTexture = Texture(std::string(TEXTURE_DIR) + "brick.png");
    brickTexture.LoadTextureA();
    dirtTexture = Texture(std::string(TEXTURE_DIR) + "dirt.png");
    dirtTexture.LoadTextureA();
    plainTexture = Texture(std::string(TEXTURE_DIR) + "plain.png");
    plainTexture.LoadTextureA();

    shinyMaterial = Material(1.f, 32);
    dullMaterial = Material(0.3f, 4);

    mainLight = DirectionalLight(
        glm::vec3(1.f), 0,
         0.3f, glm::vec3(2.f, -1.f, -2.f)
         );

    pointLights[0] = PointLight(
        glm::vec3(0, 0, 1),
        0.1, 1,
        glm::vec3(0.f, 0.f, 3),
        0.3f, 0.3f, 0.1f
        );

    pointLightCount++;

    pointLights[1] = PointLight(
    glm::vec3(0, 1, 0),
    0.1, 1,
    glm::vec3(0.f, 0.f, -3),
    0.3f, 0.2f, 0.1f
    );

    pointLightCount++;

    spotLights[0] = SpotLight(
    glm::vec3(1, 0, 0),
    1, 0.1,
    glm::vec3(0.f, 0, 0),
    0.3f, 0.3f, 0.1f,
    glm::vec3(0,-1,0), 20
    );

    spotLightCount++;

    projection = glm::perspective(45.f, (GLfloat)mainWindow.GetWidth()/mainWindow.GetHeight(), 0.1f, 100.f);
}

void PreDraw()
{
    glClearColor(0.f, 0.f, 0.f ,1.f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Draw()
{
    GLint uniformProjection = 0, uniformModel = 0, uniformView = 0, uniformEyePosition = 0,
    uniformSpecularIntensity = 0, uniformShininess = 0;

    if (shaderList[0])
    {
        [[likely]]
        shaderList[0]->UseShader();
        uniformModel = shaderList[0]->GetModelLocation();
        uniformProjection = shaderList[0]->GetProjectionLocation();
        uniformView = shaderList[0]->GetViewLocation();
        uniformEyePosition = shaderList[0]->GetEyePositionLocation();
        uniformSpecularIntensity = shaderList[0]->GetSpecularIntensityLocation();
        uniformShininess = shaderList[0]->GetShininessLocation();

        shaderList[0]->SetDirectionalLight(&mainLight);
        shaderList[0]->SetPointLights(pointLights, pointLightCount);
        shaderList[0]->SetSpotLights(spotLights, spotLightCount);
    }

    glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, value_ptr(projection));
    glUniformMatrix4fv(uniformView, 1, GL_FALSE, value_ptr(camera.CalculateViewMatrix()));
    glUniform3f(uniformEyePosition, camera.getLocation().x, camera.getLocation().y, camera.getLocation().z);

    auto model = glm::mat4(1.0f);

    model = translate(model, glm::vec3(0.f, 0.f, -2.5f));
    //model = scale(model, glm::vec3(0.4f, 0.4f, 1.0f));

    glUniformMatrix4fv(uniformModel, 1, GL_FALSE, value_ptr(model));
    dirtTexture.UseTexture();
    dullMaterial.UseMaterial(uniformSpecularIntensity, uniformShininess);
    if (meshList[0])
    {
        [[likely]]
        meshList[0]->RenderMesh();
    }

    model = glm::mat4(1.0f);
    model = translate(model, glm::vec3(0.f, 0, 2.5f));
    //model = scale(model, glm::vec3(0.4f, 0.4f, 1.0f));
    glUniformMatrix4fv(uniformModel, 1, GL_FALSE, value_ptr(model));
    brickTexture.UseTexture();
    shinyMaterial.UseMaterial(uniformSpecularIntensity, uniformShininess);
    if (meshList[1])
    {
        [[likely]]
        meshList[1]->RenderMesh();
    }

    model = glm::mat4(1.0f);
    model = translate(model, glm::vec3(0.f, -2, 0));
    //model = scale(model, glm::vec3(0.4f, 0.4f, 1.0f));
    glUniformMatrix4fv(uniformModel, 1, GL_FALSE, value_ptr(model));
    dirtTexture.UseTexture();
    dullMaterial.UseMaterial(uniformSpecularIntensity, uniformShininess);
    if (meshList[2])
    {
        [[likely]]
        meshList[2]->RenderMesh();
    }

    glUseProgram(0);
}

void calcAverageNormals(unsigned *indices, unsigned indexCount, GLfloat *vertices, unsigned vertexCount,
    unsigned vertexLength, unsigned normalOffset)
{
    for (size_t i = 0; i < indexCount; i += 3)
    {
        unsigned in0 = indices[i] * vertexLength;
        unsigned in1 = indices[i + 1] * vertexLength;
        unsigned in2 = indices[i + 2] * vertexLength;

        glm::vec3 v1(
            vertices[in1] - vertices[in0],
            vertices[in1 + 1] - vertices[in0 + 1],
            vertices[in1 + 2] - vertices[in0 + 2]
            );
        glm::vec3 v2(
            vertices[in2] - vertices[in0],
            vertices[in2 + 1] - vertices[in0 + 1],
            vertices[in2 + 2] - vertices[in0 + 2]
        );
        glm::vec3 normal = glm::cross(v1, v2);
        normal = glm::normalize(normal);

        in0 += normalOffset; in1 += normalOffset; in2 +=normalOffset;
        vertices[in0] += normal.x; vertices[in0 + 1] += normal.y; vertices[in0 + 2] += normal.z;
        vertices[in1] += normal.x; vertices[in1 + 1] += normal.y; vertices[in1 + 2] += normal.z;
        vertices[in2] += normal.x; vertices[in2 + 1] += normal.y; vertices[in2 + 2] += normal.z;
    }

    for (size_t i = 0; i < vertexCount / vertexLength; i++)
    {
        unsigned int nOffset = i * vertexLength + normalOffset;
        glm::vec3 vec(vertices[nOffset], vertices[nOffset + 1], vertices[nOffset + 2]);
        vec = glm::normalize(vec);
        vertices[nOffset] = vec.x; vertices[nOffset + 1] = vec.y; vertices[nOffset + 2] = vec.z;
    }
}

void CreateObjects()
{
    unsigned indices[]
    {
        0, 3, 1,
        1, 3, 2,
        2, 3, 0,
        0, 1, 2,
    };
    
    GLfloat vertices[]
    {
        // x    y    z      u    v      nx   ny   nz
        -1.f, -1.f, -0.6f,  0.f, 0.f,   0.f, 0.f, 0.f,
        0.f, -1.f, 1.f,     0.5f, 0.f,  0.f, 0.f, 0.f,
        1.f, -1.f, -0.6f,   1.f, 0.f,   0.f, 0.f, 0.f,
        0.f, 1.f, 0.f,      0.5f, 1.f,  0.f, 0.f, 0.f
    };

    unsigned floorIndices[]
    {
        0, 2, 1,
        1, 2, 3,
    };

    GLfloat floorVertices[]
    {
        -10, 0, -10,    0, 0,       0, -1, 0,
        10, 0, -10,     10, 0,      0, -1, 0,
        -10, 0, 10,     0, 10,      0, -1, 0,
        10, 0, 10,      10, 10,     0, -1, 0,
    };

    calcAverageNormals(indices, 12, vertices, 32, 8, 5);

    auto *obj1 = new Mesh();
    obj1->CreateMesh(vertices, indices, 32, 12);
    meshList.push_back(obj1);

    auto *obj2 = new Mesh();
    obj2->CreateMesh(vertices, indices, 32, 12);
    meshList.push_back(obj2);

    auto *obj3 = new Mesh();
    obj3->CreateMesh(floorVertices, floorIndices, 32, 6);
    meshList.push_back(obj3);
}

void MainLoop()
{
    while(!gQuit)
    {
        now = SDL_GetPerformanceCounter();
        deltaTime = (now - lastTime)*1000 / SDL_GetPerformanceFrequency();
        lastTime = now;

        camera.Control(static_cast<float>(deltaTime));
        mainWindow.UpdateWindow();

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