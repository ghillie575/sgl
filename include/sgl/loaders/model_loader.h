#ifndef MODEL_LOADER_H
#define MODEL_LOADER_H
#define SGL_MODEL_LOADER_VERSION "1.0"
#include <string>
#include <sgl/core/model.h>
struct ModelInfo
{
    std::string name;
    std::string path;
    std::string loader_version;
};

void loadModelHeaders();
Model *getModelByName(const std::string &name);
int loadModel(const std::string &name);
#endif