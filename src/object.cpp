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
#include <random>
GameObject::GameObject()
{
    this->transform.setScaling(glm::vec3(1,1,1));
    this->id = generateRandomID(10);
}
void GameObject::loadModel(const char *modelName)
{
    std::string path = "engine/models/";
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
    float f;
    while (iss >> f)
    {
        v.push_back(f);
    }

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

void GameObject::build()
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

void GameObject::useShader(const char *shaderName)
{
    this->shaderName = shaderName;
}
void GameObject::useShader(Shader* shader)
{
    this->shader = shader;
}
std::string GameObject::generateRandomID(int length) {
    // Create a random number generator
    std::random_device rd;  // Obtain a random number from hardware
    std::mt19937 eng(rd()); // Seed the generator

    // Define the range for digits (0-9)
    std::uniform_int_distribution<> distr(0, 9);

    std::string id;
    for (int i = 0; i < length; ++i) {
        id += std::to_string(distr(eng)); // Generate a random digit and append to the ID
    }

    return id;
}
void GameObject::render()
{
    
    //trans = glm::translate(trans,pos);
    glm::mat4 model = transform.getTransformationMatrix();
    
    
    shader->use();
    shader->setMat4("model", model);
    
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
void GameObject::freeResources()
{
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
}
void GameObject::setDrawMode(drawAs mode)
{
    this->mode = mode;
}