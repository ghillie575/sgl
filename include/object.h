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
    unsigned int texture;
    Logger logger = Logger("",true);
    std::string generateRandomID(int length);
    glm::vec4 color = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);

public:
    std::string id;
    std::string name = "x";
    Shader* shader = nullptr;
    std::string shaderName = "";
    unsigned int VBO, VAO, EBO;
    Transform transform;
    drawAs mode;
    std::vector<unsigned int> ind;
    std::vector<float> vert;
    int polCount;
    GameObject();
    virtual void build();
    virtual void render();
    void useShader(const char* shaderName);
    void useShader(Shader* shader);
    void freeResources();
    void setDrawMode(drawAs mode);
    void loadModel(std::string modelName);
    void printModelData();
    void useTexture(std::string texturePath);
    void setColor(glm::vec4 color);
};

#endif