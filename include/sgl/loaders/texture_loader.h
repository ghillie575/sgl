#ifndef TEXTURE_LOADER_H
#define TEXTURE_LOADER_H
#include <string>
#include <sgl/core/texture.h>
#include <sgl/logger.h>
#include <vector>

Texture* getTextureByFileName(const std::string& fileName);
int loadTexture(const std::string& fileName);
void loadTextureHeaders();
#endif
