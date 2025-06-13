#include <SGL/texture.h>
#include <stbi/stb_image.h>
#include <SGL/error_handler.h>
#include <SGL/logger.h>
#include <fstream>
using namespace SGL;
int Texture::loadTexture(std::string texturePath)
{
    if (!std::ifstream("engine/textures/" + texturePath))
    {
        logger.log(LogLevel::ERROR, "Texture file does not exist: " + texturePath);
        handle_error("Failed to load texture: " + texturePath);
        return loadTexture("blank.jpg");
    }
    logger.log(LogLevel::DEBUG, "Generating texture...");
    glGenTextures(1, &ID);
    glBindTexture(GL_TEXTURE_2D, ID);
    logger.log(LogLevel::DEBUG, "Texture bound to GL_TEXTURE_2D");

    // Setting texture wrapping parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    logger.log(LogLevel::DEBUG, "Texture wrapping parameters set to GL_REPEAT");

    // Setting texture filtering parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    logger.log(LogLevel::DEBUG, "Texture filtering parameters set to GL_LINEAR");

    // Load image, create texture and generate mipmaps
    int width, height, nrChannels;
    std::string texturePathStr = "engine/textures/";
    texturePathStr.append(texturePath);
    logger.log(LogLevel::DEBUG, "Loading texture from " + texturePathStr);
    unsigned char *data = stbi_load(texturePathStr.c_str(), &width, &height, &nrChannels, 0);
    if (data)
    {
        logger.log(LogLevel::DEBUG, "Texture loaded successfully");
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
        logger.log(LogLevel::DEBUG, "Texture image set and mipmaps generated");
    }
    else
    {
        logger.log(LogLevel::ERROR, "Failed to load texture " + texturePath);
        handle_error("Failed to load texture: " + texturePath);
    }
    stbi_image_free(data);
    return 0;
}
void Texture::useTexture()
{
    glBindTexture(GL_TEXTURE_2D, ID);
}