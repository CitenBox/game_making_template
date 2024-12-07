//
// Created by troll on 12/7/2024.
//
#pragma once

#include <glad/glad.h>
#include <string>

class Shader
{
public:
    Shader();
    ~Shader();

    void CreateFromString(const std::string& vertexCode, const std::string& fragmentCode);
    void CreateFromFile(const std::string& vertexPath, const std::string& fragmentPath);
    std::string LoadShaderAsString(const std::string& filename);

    void UseShader() const;
    void ClearShader();

    [[nodiscard]] GLint GetProjectionLocation() const {  return uniformProjection; }
    [[nodiscard]] GLint GetModelLocation() const {  return uniformModel; }

protected:
    GLuint shaderID;
    GLint uniformProjection, uniformModel;

    void CompileShader(const char* vertexCode, const char* fragmentCode);
    void AddShader(GLuint theProgram, const char* shaderCode, GLenum shaderType);
};
