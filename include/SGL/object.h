#include <vector>
#include <iostream>
#include <SGL/shader.h>
#include <cstddef>
#include <glm/glm.hpp>
#include <SGL/transform.h>
#include <SGL/logger.h>
#include <SGL/component.h>
#include <SGL/window.h> 
#ifndef OBJECT_H
#define OBJECT_H
class Window;
enum drawAs
{
    lines,
    triangles
};
class Component;
class GameObject
{
private:
    /* data */
    bool modelUsesEBO = true;
    
    unsigned int texture;
    Logger logger = Logger("");
    std::string generateRandomID(int length);
    glm::vec4 color = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
    

public:
    bool debug = false;
    std::vector<std::shared_ptr<Component>> components;
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
    void start();
    void addComponent(Window* window, std::string type);
    void debugger();
};

#endif