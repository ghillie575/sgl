#include <object.h>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <cstddef>
#include <sstream>
#include <iterator>
#include <fstream>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
Object::Object()
{
    this->scale = glm::vec3(1,1,1);
}
void Object::translate(glm::vec3 vector,float speed){
    glm::vec3 translate = glm::vec3((float)glfwGetTime() * speed);
    pos += vector * translate;
    return ;
}
void Object::loadModel(const char *modelName)
{
    std::string path = "models/";
    path.append(modelName);
    path.append(".vmodel");
    std::ifstream t(path);
    std::stringstream buffer;
    buffer << t.rdbuf();

    // If possible, always prefer std::vector to naked array
    std::vector<float> v;

    // Build an istream that holds the input string
    std::istringstream iss(buffer.str());

    // Iterate over the istream, using >> to grab floats
    // and push_back to store them in the vector
    std::copy(std::istream_iterator<float>(iss),
              std::istream_iterator<float>(),
              std::back_inserter(v));

    // Put the result on standard out
    this->vert = v;
    t.close();
    // Indicies
    path = "engine/models/";
    path.append(modelName);
    path.append(".imodel");
    std::ifstream t1(path);
    std::stringstream buffer1;
    buffer1 << t1.rdbuf();

    // If possible, always prefer std::vector to naked array
    std::vector<unsigned int> i;

    // Build an istream that holds the input string
    std::istringstream iss1(buffer1.str());

    // Iterate over the istream, using >> to grab floats
    // and push_back to store them in the vector
    std::copy(std::istream_iterator<unsigned int>(iss1),
              std::istream_iterator<unsigned int>(),
              std::back_inserter(i));
    this->ind = i;
    polCount = i.size();
    t.close();
}

void Object::build()
{

    float vertices[vert.size()];
    unsigned int indices[ind.size()];
    std::copy(vert.begin(), vert.end(), vertices);
    std::copy(ind.begin(), ind.end(), indices);
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
    if (mode == lines)
    {
        glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void *)0);
    }
    else
    {
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *)0);
    }
    // glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void Object::useShader(const char *shaderName)
{
    std::string name = "engine/shaders/";
    name += shaderName;
    std::string vertex = name + ".vs";
    std::string fragment = name + ".fs";
    shader = Shader(vertex.c_str(), fragment.c_str());
}
void Object::useShader(Shader shader)
{
    this->shader = shader;
}
void Object::setScale(glm::vec3 scale){
    this->scale = scale;
}  
void Object::setPosition(glm::vec3 pos){
    this->pos = pos;
}   
void Object::render()
{
    
    //trans = glm::translate(trans,pos);
    glm::mat4 trans = glm::mat4(1.0f);
    trans = glm::translate(trans, pos);
    trans = glm::scale(trans,scale);
    shader.use();
    unsigned int transformLoc = glGetUniformLocation(shader.ID, "transform");
    glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(trans));
    glBindVertexArray(VAO);

    if (mode == lines)
    {
        glDrawElements(GL_LINES, polCount, GL_UNSIGNED_INT, 0);
    }
    else
    {
        glDrawElements(GL_TRIANGLES, polCount, GL_UNSIGNED_INT, 0);
    }
}
void Object::freeResources()
{
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
}
void Object::setDrawMode(drawAs mode)
{
    this->mode = mode;
}