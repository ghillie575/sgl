#include <sgl/loaders/texture_loader.h>
#include <sgl/logger.h>
#include <vector>
#include <filesystem>
#include <unordered_map>

std::vector<std::string> textureFileNames;                   // Only file names (e.g., "brick.png")
std::vector<Texture *> textures;                             // Loaded texture objects
std::unordered_map<std::string, std::string> texturePathMap; // fileName -> full path

Texture *getTextureByFileName(const std::string &fileName)
{
    auto it = texturePathMap.find(fileName);
    if (it == texturePathMap.end())
    {
        getLogger()->warn("TextureLoader", "Texture not found in header list: " + fileName);
        return nullptr;
    }
    // Check if already loaded
    for (auto *tex : textures)
    {
        if (tex->path == it->second)
        {
            return tex;
        }
    }

    getLogger()->log("TextureLoader", "Loading texture: " + fileName);

    Texture *texture = new Texture();
    texture->path = it->second; // full path

    if (texture->load(CLAMP_REPEAT, FILTER_LINEAR) != 0)
    {
        getLogger()->error("TextureLoader", "Failed to load texture: " + fileName);
        delete texture;
        return nullptr;
    }

    textures.push_back(texture);
    getLogger()->debug("TextureLoader", "Texture loaded successfully: " + fileName);
    return texture;
}

void loadTextureHeaders()
{
    namespace fs = std::filesystem;
    std::string texturesDir = "engine/textures";

    getLogger()->log("TextureLoader", "Loading texture headers from directory: " + texturesDir);

    textureFileNames.clear();
    texturePathMap.clear();

    for (const auto &entry : fs::directory_iterator(texturesDir))
    {
        if (!entry.is_regular_file())
            continue;

        std::string filePath = entry.path().string();
        std::string fileName = entry.path().filename().string();

        textureFileNames.push_back(fileName);
        texturePathMap[fileName] = filePath;

        getLogger()->debug("TextureLoader", "Found texture: " + fileName + " (" + filePath + ")");
    }

    getLogger()->log("TextureLoader", "Total textures found: " + std::to_string(textureFileNames.size()));
}

int loadTexture(const std::string &fileName)
{
    getLogger()->log("TextureLoader", "Loading texture: " + fileName);

    auto it = texturePathMap.find(fileName);
    if (it == texturePathMap.end())
    {
        getLogger()->warn("TextureLoader", "Texture not found: " + fileName);
        return -1; // Not found
    }

    Texture *texture = new Texture();
    texture->path = it->second; // full path

    if (texture->load(CLAMP_REPEAT, FILTER_LINEAR) != 0)
    {
        getLogger()->error("TextureLoader", "Failed to load texture: " + fileName);
        delete texture;
        return -2;
    }

    textures.push_back(texture);
    getLogger()->debug("TextureLoader", "Texture loaded successfully: " + fileName);
    return 0;
}
