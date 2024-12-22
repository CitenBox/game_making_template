//
// Created by troll on 12/15/2024.
//

#ifndef TEXTURE_H
#define TEXTURE_H

#include <glad/glad.h>
#include <string>

class Texture
{
public:
    Texture() = default;
    Texture(const std::string& fileLocation): fileLocation(fileLocation){}
    ~Texture();

    void LoadTexture();
    void UseTexture();
    void ClearTexture();

protected:
    GLuint textureID = 0;
    int width = 0, height = 0, bitDepth = 0;

    std::string fileLocation;
};



#endif //TEXTURE_H
