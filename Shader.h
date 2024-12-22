//
// Created by troll on 12/7/2024.
//
#pragma once

#include <glad/glad.h>
#include <string>

class Shader
{
public:
    Shader() = default;
    ~Shader();

    void CreateFromString(const std::string& vertexCode, const std::string& fragmentCode);
    void CreateFromFile(const std::string& vertexPath, const std::string& fragmentPath);
    std::string LoadShaderAsString(const std::string& filename);

    void UseShader() const;
    void ClearShader();

    [[nodiscard]] GLint GetProjectionLocation() const {  return uniformProjection; }
    [[nodiscard]] GLint GetModelLocation() const {  return uniformModel; }
    [[nodiscard]] GLint GetViewLocation() const {  return uniformView; }
    [[nodiscard]] GLint GetAmbientIntensityLocation() const {  return uniformAmbientIntensity; }
    [[nodiscard]] GLint GetAmbientColorLocation() const {  return uniformAmbientColor; }
    [[nodiscard]] GLint GetDiffuseIntensityLocation() const {  return uniformDiffuseIntensity; }
    [[nodiscard]] GLint GetDirectionLocation() const {  return uniformDirection; }
    [[nodiscard]] GLint GetSpecularIntensityLocation() const {  return uniformSpecularIntensity; }
    [[nodiscard]] GLint GetShininessLocation() const {  return uniformShininess; }
    [[nodiscard]] GLint GetEyePositionLocation() const {  return uniformEyePosition; }


protected:
    GLuint shaderID;
    GLint uniformProjection, uniformModel, uniformView, uniformEyePosition,
    uniformAmbientIntensity, uniformAmbientColor, uniformDiffuseIntensity, uniformDirection,
    uniformSpecularIntensity, uniformShininess;

    void CompileShader(const char* vertexCode, const char* fragmentCode);
    void AddShader(GLuint theProgram, const char* shaderCode, GLenum shaderType);
};
