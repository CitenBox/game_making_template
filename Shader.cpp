//
// Created by troll on 12/7/2024.
//

#include "Shader.h"

#include <iostream>
#include <cstring>
#include <fstream>


Shader::Shader()
{
    shaderID = 0;
    uniformModel = 0;
    uniformProjection = 0;
}

Shader::~Shader()
{
    ClearShader();
}

void Shader::CreateFromString(const std::string &vertexCode, const std::string &fragmentCode)
{
    CompileShader(vertexCode.c_str(), fragmentCode.c_str());
}

void Shader::CreateFromFile(const std::string &vertexPath, const std::string &fragmentPath)
{
    CreateFromString(LoadShaderAsString(vertexPath), LoadShaderAsString(fragmentPath));
}

std::string Shader::LoadShaderAsString(const std::string& filename)
{
    std::string result;
    std::ifstream myFile(filename.c_str());
    if(myFile.is_open())
    {
        std::string line;
        while(std::getline(myFile, line))
        {
            result += line + '\n';
        }
        myFile.close();
    }
    else
    {
        std::cout << "Could not open file: " << filename << '\n';
        return "";
    }

    return result;
}

void Shader::UseShader() const
{
    glUseProgram(shaderID);
}

void Shader::ClearShader()
{
    if (shaderID != 0)
    {
        glDeleteProgram(shaderID);
        shaderID = 0;
    }

    uniformModel = 0;
    uniformProjection = 0;
}


void Shader::CompileShader(const char* vertexCode, const char* fragmentCode)
{
    shaderID = glCreateProgram();

    if(!shaderID)
    {
        std::cout << "Failed to create shader program!\n";
        return;
    }

    AddShader(shaderID, vertexCode, GL_VERTEX_SHADER);
    AddShader(shaderID, fragmentCode, GL_FRAGMENT_SHADER);

    GLint result = 0;
    GLchar eLog[1024] = {   0   };

    glLinkProgram(shaderID);
    glGetProgramiv(shaderID, GL_LINK_STATUS, &result);
    if(!result)
    {
        glGetProgramInfoLog(shaderID, sizeof(eLog), 0, eLog);
        std::cout << "Error linking program: " << eLog << '\n';
        return;
    }

    glValidateProgram(shaderID);
    glGetProgramiv(shaderID, GL_VALIDATE_STATUS, &result);
    if(!result)
    {
        glGetProgramInfoLog(shaderID, sizeof(eLog), 0, eLog);
        std::cout << "Error validating program: " << eLog << '\n';
        return;
    }

    uniformModel = glGetUniformLocation(shaderID, "model");
    uniformProjection = glGetUniformLocation(shaderID, "projection");
}

void Shader::AddShader(GLuint theProgram, const char *shaderCode, GLenum shaderType)
{
    GLuint theShader = glCreateShader(shaderType);

    const GLchar* theCode[1];
    theCode[0] = shaderCode;

    GLint codeLength[1];
    codeLength[0] = strlen(shaderCode);

    glShaderSource(theShader, 1, theCode, codeLength);
    glCompileShader(theShader);

    GLint result = 0;
    GLchar eLog[1024]  = {0};

    glGetShaderiv(theShader, GL_COMPILE_STATUS, &result);
    if(!result)
    {
        glGetShaderInfoLog(theShader, sizeof(eLog), 0, eLog);
        std::cout << "Error compiling the " << shaderType << " shader: " << eLog << '\n';
        return;
    }

    glAttachShader(theProgram, theShader);
}
