#ifndef SHADER_LOADER_H
#define SHADER_LOADER_H
#define SGL_LOADER_VERSION "1.0"
#include <string>
#include <sgl/engine/shader.h>
struct ShaderPartInfo {
    std::string loader_version;
    std::string path;
    std::string name;
    std::string type;
};
struct ShaderInfo {
    bool valid;
    std::string name;
    ShaderPartInfo fragment;
    ShaderPartInfo vertex;
};
void loadShaderHeaders();
Shader *getShaderByName(const std::string& name);
int loadShader(const std::string& name);
#endif