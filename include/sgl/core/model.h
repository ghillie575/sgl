#ifndef MODEL_H
#define MODEL_H
#include <string>
class Model {
public:
    std::string name;
    float *vertices;
    unsigned int *indices;
    float *texcoords;
    size_t vertexCount;
    size_t indexCount;
    size_t texcoordCount;

    Model()
        : vertices(nullptr), indices(nullptr), texcoords(nullptr),
          vertexCount(0), indexCount(0), texcoordCount(0) {}

    ~Model() {
        delete[] vertices;
        delete[] indices;
        delete[] texcoords;
    }
};
#endif