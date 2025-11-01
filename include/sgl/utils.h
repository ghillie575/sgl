#ifndef UTILS_H
#define UTILS_H
#include <string>
#include <vector>
#include <sgl/core/gameobject.h>
#include <sgl/debug/debug_label.h>
enum ResourceType
{
    RESOURCE_SHADER,
    RESOURCE_MODEL,
    RESOURCE_FONT,
    RESOURCE_TEXTURE
};
void require(const std::string &name, ResourceType type);
GameObject *createGameObject(std::string model, std::string shader);
GameObject *createGameObject(std::string model, std::string shader, std::string texture);
DebugLabel* createDebugLabel(std::string text,float relativeX,float relativeY,float size);
#endif