#include <sgl/utils.h>
#include <sgl/logger.h>
#include <sgl/loaders/shader_loader.h>
#include <sgl/loaders/model_loader.h>
#include <sgl/core/texture.h>
#include <sgl/loaders/texture_loader.h>
void require(const std::string &name, ResourceType type)
{
    if (type == RESOURCE_SHADER)
    {
        if (loadShader(name) != 0)
        {
            getLogger()->error("REQUIRE", "Failed to load required shader: " + name + ". exiting.");
            exit(EXIT_FAILURE);
        }
        else
        {
        }
    }
    else if (type == RESOURCE_MODEL)
    {
        if (loadModel(name) != 0)
        {
            getLogger()->error("REQUIRE", "Failed to load required model: " + name + ". exiting.");
            exit(EXIT_FAILURE);
        }
    }
    else if (type == RESOURCE_TEXTURE)
    {
        if (loadTexture(name) != 0)
        {
            getLogger()->error("REQUIRE", "Failed to load required texture: " + name + ". exiting.");
            exit(EXIT_FAILURE);
        }
    }
    else if (type == RESOURCE_FONT)
    {
        getLogger()->warn("REQUIRE", "Font resource loading not implemented yet.");
    }
    else
    {
        getLogger()->warn("REQUIRE", "Unknown resource type requested");
    }
}
GameObject *createGameObject(std::string model, std::string shader)
{
    Shader *oShader = getShaderByName(shader);
    if (!oShader)
    {
        getLogger()->error("INIT", "Failed to retrieve required shader");
        return nullptr;
    }
    Model *oModel = getModelByName(model);
    if (!oModel)
    {
        getLogger()->error("INIT", "Failed to retrieve required model");
        return nullptr;
    }

    GameObject *out = new GameObject(oModel, oShader);
    return out;
}
GameObject *createGameObject(std::string model, std::string shader, std::string texture)
{
    Shader *oShader = getShaderByName(shader);
    if (!oShader)
    {
        getLogger()->error("INIT", "Failed to retrieve required shader");
        return nullptr;
    }
    Model *oModel = getModelByName(model);
    if (!oModel)
    {
        getLogger()->error("INIT", "Failed to retrieve required model");
        return nullptr;
    }
    Texture *oTexture = getTextureByFileName(texture);
    if (!oTexture)
    {
        getLogger()->error("INIT", "Failed to retrieve required texture");
        return nullptr;
    }
    GameObject *out = new GameObject(oModel, oShader, oTexture);
    out->begin();
    out->setPosition(glm::vec3(0, 0, 0));
    out->setRotation(glm::vec3(0, 0, 0));
    out->setScale(glm::vec3(1, 1, 1));
    return out;
}
DebugLabel *createDebugLabel(std::string text, float relativeX, float relativeY,float size)
{
    require("debug_text", ResourceType::RESOURCE_SHADER);
    require("debug.ttf", ResourceType::RESOURCE_FONT);
    DebugLabel *label = new DebugLabel(text);
    label->x = relativeX;
    label->y = relativeY;
    label->scale = size;
    if(label->init() !=0){
        return nullptr;
    }
    return label;
}
