#ifndef MODEL_LOADER_H
#define MODEL_LOADER_H
#include <string>
struct ModelInfo {
    bool valid;
    std::string name;
    std::string path;
};
class Model {
public:
    std::string name;
    float *vertices;
    unsigned int *indices;
};

void loadModelHeaders();
Model* getModelByName(const std::string& name);
int loadModel(const std::string& name);
#endif