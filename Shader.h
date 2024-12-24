//
// Created by troll on 12/7/2024.
//
#pragma once

#include <glad/glad.h>
#include <string>
#include "CommonValues.h"

class Shader
{
public:
    explicit Shader() = default;
    ~Shader();

    void CreateFromString(const std::string& vertexCode, const std::string& fragmentCode);
    void CreateFromFile(const std::string& vertexPath, const std::string& fragmentPath);
    std::string LoadShaderAsString(const std::string& filename);

    void UseShader() const;
    void ClearShader();

    [[nodiscard]] GLint GetProjectionLocation() const {  return uniformProjection; }
    [[nodiscard]] GLint GetModelLocation() const {  return uniformModel; }
    [[nodiscard]] GLint GetViewLocation() const {  return uniformView; }
    [[nodiscard]] GLint GetAmbientIntensityLocation() const {  return uniformDirectionalLight.uniformAmbientIntensity; }
    [[nodiscard]] GLint GetColorLocation() const {  return uniformDirectionalLight.uniformColor; }
    [[nodiscard]] GLint GetDiffuseIntensityLocation() const {  return uniformDirectionalLight.uniformDiffuseIntensity; }
    [[nodiscard]] GLint GetDirectionLocation() const {  return uniformDirectionalLight.uniformDirection; }
    [[nodiscard]] GLint GetSpecularIntensityLocation() const {  return uniformSpecularIntensity; }
    [[nodiscard]] GLint GetShininessLocation() const {  return uniformShininess; }
    [[nodiscard]] GLint GetEyePositionLocation() const {  return uniformEyePosition; }

    void SetDirectionalLight(class DirectionalLight *directionalLight) const;
    void SetPointLights(class PointLight *pointLights, unsigned lightCount);

protected:
    unsigned pointLightCount = 0;

    GLuint shaderID;
    GLint uniformProjection, uniformModel, uniformView, uniformEyePosition,
    uniformSpecularIntensity, uniformShininess;

    struct
    {
        GLint uniformColor;
        GLint uniformAmbientIntensity;
        GLint uniformDiffuseIntensity;

        GLint uniformDirection;

    } uniformDirectionalLight;

    GLint uniformPointLightCount;

    struct
    {
        GLint uniformColor;
        GLint uniformAmbientIntensity;
        GLint uniformDiffuseIntensity;

        GLint uniformPosition;
        GLint uniformConstant;
        GLint uniformLinear;
        GLint uniformExponent;

    } uniformPointLights[MAX_POINT_LIGHTS];

    void CompileShader(const char* vertexCode, const char* fragmentCode);
    void AddShader(GLuint theProgram, const char* shaderCode, GLenum shaderType);
};
