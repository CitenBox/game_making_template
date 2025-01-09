#pragma once

#include <glad/glad.h>

class Mesh
{
public:
    explicit Mesh() = default;

    void CreateMesh(GLfloat* vertices, unsigned int* indices, unsigned int numOfVertices, unsigned int numOfIndices);
    void RenderMesh() const;
    void ClearMesh();
    
    ~Mesh();

protected:
    GLuint VAO, VBO, IBO;
    GLsizei IndexCount;
};
