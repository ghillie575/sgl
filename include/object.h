#include <vector>
#include <iostream>
#include <shader.h>
#include <cstddef>
#include <glm/glm.hpp>
#ifndef OBJECT_H
#define OBJECT_H

enum drawAs
{
    lines,
    triangles
};
class Object
{
private:
    /* data */
    bool modelUsesEBO = true;

public:
    Shader shader = Shader();
    unsigned int VBO, VAO, EBO;
    glm::vec3 scale;   
    glm::vec3 pos; 
    //glm::mat4 trans;
    drawAs mode;
    std::vector<unsigned int> ind;
    std::vector<float> vert;
    int polCount;
    Object();
    void build();
    void render();
    void useShader(const char* shaderName);
    void useShader(Shader shader);
    //void recompileShader();
    void setScale(glm::vec3 scale);
    void setPosition(glm::vec3 pos);
    void setRotation(glm::vec3 rotation);
    void translate(glm::vec3 vector,float speed);
    void freeResources();
    void setDrawMode(drawAs mode);
    void loadModel(const char *modelName);
};

#endif