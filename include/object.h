#include <vector>
#include <iostream>
#include <shader.h>
#include <cstddef>
#include <glm/glm.hpp>
#include <transform.h>
#include <logger.h>
#ifndef OBJECT_H
#define OBJECT_H

enum drawAs
{
    lines,
    triangles
};
class GameObject
{
private:
    /* data */
    bool modelUsesEBO = true;
    Logger logger = Logger("");

public:
    Shader* shader = nullptr;
    std::string shaderName = "";
    unsigned int VBO, VAO, EBO;
    Transform transform;
    drawAs mode;
    std::vector<unsigned int> ind;
    std::vector<float> vert;
    int polCount;
    GameObject();
    void build();
    void render();
    void useShader(const char* shaderName);
    void useShader(Shader* shader);
    void freeResources();
    void setDrawMode(drawAs mode);
    void loadModel(const char *modelName);
    void logInfo(const char* message);
    void logError(const char* message);
};

#endif