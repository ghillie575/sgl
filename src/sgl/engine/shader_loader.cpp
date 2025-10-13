#include <sgl/engine/shader_loader.h>
#include <sgl/logger.h>
#include <fstream>
#include <sstream>
#include <iostream>
#include <vector>
#include <filesystem>
std::vector<ShaderInfo> shaderInfos; // Store shader metadata
std::vector<Shader *> shaders;       // Store compiled shader programs
Shader *getShaderByName(const std::string &name)
{
    for (size_t i = 0; i < shaderInfos.size(); ++i)
    {
        if (shaderInfos[i].name == name)
        {
            for (size_t i = 0; i < shaders.size(); i++)
            {
                if (shaders[i]->name == name)
                    return shaders[i]; // Return existing shader
            }
            getLogger()->log("Shader", "Compiling: " + name);
            Shader *shader = new Shader(shaderInfos[i].vertex.path.c_str(), shaderInfos[i].fragment.path.c_str());
            shaders.push_back(shader);
            shader->name = name;
            return shader;
        }
    }
    getLogger()->warn("ShaderLoader", "Shader not found: " + name);
    return nullptr;
}
int loadShader(const std::string &name)
{
    for (size_t i = 0; i < shaderInfos.size(); ++i)
    {
        if (shaderInfos[i].name == name)
        {
            for (size_t i = 0; i < shaders.size(); i++)
            {
                if (shaders[i]->name == name)
                    return 0;
            }
            getLogger()->log("Shader", "Compiling: " + name);
            Shader *shader = new Shader(shaderInfos[i].vertex.path.c_str(), shaderInfos[i].fragment.path.c_str());
            shaders.push_back(shader);
            shader->name = name;
            return 0; // Success
        }
    }
    getLogger()->warn("ShaderLoader", "Shader not found: " + name);
    return -1; // Failure
}
void loadShaderHeaders()
{

    namespace fs = std::filesystem;
    std::string shadersDir = "engine/shaders";

    for (const auto &entry : fs::directory_iterator(shadersDir))
    {
        if (!entry.is_regular_file())
            continue;
        std::ifstream file(entry.path());
        if (!file.is_open())
            continue;
        std::string firstLine;
        std::getline(file, firstLine);

        // Parse line like: //<<sgl.shader.loader=1.0;type=vertex;path=engine/shaders/default_vs.glsl;name=default_vs;>>//
        size_t start = firstLine.find("//<<");
        size_t end = firstLine.find(">>//");
        if (start == std::string::npos || end == std::string::npos)
            continue;
        std::string meta = firstLine.substr(start + 4, end - (start + 4));

        ShaderPartInfo info;
        std::istringstream ss(meta);
        std::string token;
        while (std::getline(ss, token, ';'))
        {
            size_t eq = token.find('=');
            if (eq == std::string::npos)
                continue;
            std::string key = token.substr(0, eq);
            std::string value = token.substr(eq + 1);
            if (key == "sgl.shader.loader")
                info.loader_version = value;
            else if (key == "type")
                info.type = value;
            else if (key == "path")
                info.path = value;
            else if (key == "name")
                info.name = value;
        }
        if (info.loader_version != SGL_LOADER_VERSION)
        {
            getLogger()->warn("ShaderLoader", "Incompatible loader version for shader: " + info.name + ". Expected " + SGL_LOADER_VERSION + ", got " + info.loader_version + ". Skipping.");
            continue;
        }
        if (info.type != "vertex" && info.type != "fragment")
        {
            getLogger()->warn("ShaderLoader", "Unknown shader type for shader: " + info.name + ": " + info.type + ". Skipping.");
            continue;
        }
        if (info.path.empty() || info.name.empty())
        {
            getLogger()->warn("ShaderLoader", "Incomplete shader metadata in file: " + entry.path().string() + ". Skipping.");
            continue;
        }
        getLogger()->log("ShaderLoader", "Loaded shader metadata: " + info.name + " (" + info.type + ")");
        bool found = false;
        for (auto &existingInfo : shaderInfos)
        {
            if (existingInfo.name == info.name)
            {
                if (info.type == "vertex")
                {
                    existingInfo.vertex = info;
                    existingInfo.valid = true;
                    found = true;
                    break;
                }
                else if (info.type == "fragment")
                {
                    existingInfo.fragment = info;
                    existingInfo.valid = true;
                    found = true;
                    break;
                }
            }
        }
        if (found)
        {
            continue;
        }
        ShaderInfo minfo;
        minfo.name = info.name;
        if (info.type == "vertex")
            minfo.vertex = info;
        else if (info.type == "fragment")
            minfo.fragment = info;
        minfo.valid = false;
        shaderInfos.push_back(minfo);
    }
    getLogger()->log("ShaderLoader", "Total shaders loaded: " + std::to_string(shaderInfos.size()));
    for (const auto &si : shaderInfos)
    {
        if (si.valid)
        {
            getLogger()->log("ShaderLoader", "Shader ready: " + si.name + " (Vertex: " + si.vertex.path + ", Fragment: " + si.fragment.path + ")" + " loader version: " + si.vertex.loader_version);
        }
        else
        {
            getLogger()->warn("ShaderLoader", "Shader incomplete: " + si.name);
        }
    }
}