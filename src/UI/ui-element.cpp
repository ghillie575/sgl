#include <SGL/UI/ui-element.h>
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
#include <stbi/stb_image.h>
#include <SGL/error_handler.h>
using namespace SGL;

namespace SGL::UI
{
    UIElement::UIElement()
    {
        this->id = generateRandomID(10);
        this->color = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
        this->position = glm::vec2(0, 0);
        this->ZIndex = 0;
    }
    void UIElement::loadTexture(std::string texturePath)
    {
        texture_str = texturePath;
        logger.log(LogLevel::DEBUG, "Generating texture...");
        glGenTextures(1, &texture);
        glBindTexture(GL_TEXTURE_2D, texture);
        logger.log(LogLevel::DEBUG, "Texture bound to GL_TEXTURE_2D");

        // Setting texture wrapping parameters
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        logger.log(LogLevel::DEBUG, "Texture wrapping parameters set to GL_REPEAT");

        // Setting texture filtering parameters
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        logger.log(LogLevel::DEBUG, "Texture filtering parameters set to GL_LINEAR");

        // Load image, create texture and generate mipmaps
        int width, height, nrChannels;
        std::string texturePathStr = "engine/textures/";
        texturePathStr.append(texturePath);
        logger.log(LogLevel::DEBUG, "Loading texture from " + texturePathStr);
        unsigned char *data = stbi_load(texturePathStr.c_str(), &width, &height, &nrChannels, 0);
        if (data)
        {
            logger.log(LogLevel::DEBUG, "Texture loaded successfully");
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
            glGenerateMipmap(GL_TEXTURE_2D);
            logger.log(LogLevel::DEBUG, "Texture image set and mipmaps generated");
        }
        else
        {
            logger.log(LogLevel::ERROR, "Failed to load texture " + texturePath);
            handle_error("Failed to load texture " + texturePath);
        }
        stbi_image_free(data);
    }
    void UIElement::setColor(glm::vec4 color) { this->color = color; }
    void UIElement::setPosition(glm::vec2 position) { this->position = position; }
    void UIElement::loadModel(std::string modelName)
    {
        // Load vertices from .vmodel file
        std::string path = "engine/models/" + modelName + ".vmodel";
        std::ifstream file(path);
        if (!file.is_open())
        {
            handle_error("Failed to load model " + path);
            throw std::runtime_error("Failed to open file: " + path);
            
        }

        std::stringstream buffer;
        buffer << file.rdbuf();
        file.close(); // Close the file after reading

        std::istringstream iss(buffer.str());
        float value;

        // Read all values into a single array
        while (iss >> value)
        {
            vert.push_back(value);
        }
        int totalSize = 5;
        for (size_t i = 0; i < vertexAttributes.size(); i++)
        {
            totalSize += vertexAttributes[i].size;
        }
        // Check if the number of values is a multiple of 5 (3 for vertex + 2 for texture coordinates)
        if (vert.size() % totalSize != 0)
        {
            handle_error("Invalid .vmodel file format: Incorrect number of values: " + std::to_string(vert.size()) + " % " + std::to_string(totalSize) + " != 0");
            throw std::runtime_error("Invalid .vmodel file format: Incorrect number of values.");
        }

        // Load indices from .imodel file
        path = "engine/models/" + modelName + ".imodel";
        std::ifstream file1(path);
        if (!file1.is_open())
        {
            handle_error("Failed to load model " + path);
            throw std::runtime_error("Failed to open file: " + path);
        }

        std::stringstream buffer1;
        buffer1 << file1.rdbuf();
        file1.close();

        std::istringstream iss1(buffer1.str());
        unsigned int index;

        // Read indices into the ind vector
        while (iss1 >> index)
        {
            ind.push_back(index);
        }

        // Calculate the number of polygons (assuming triangles)
        polCount = ind.size();
    }
    void UIElement::useShader(const char *shaderName, Window *window)
    {

        shader = window->getShader(shaderName);
    }
    void UIElement::useShader(Shader *shader)
    {
        this->shader = shader;
    }
    std::string UIElement::generateRandomID(int length)
    {
        // Create a random number generator
        std::random_device rd;  // Obtain a random number from hardware
        std::mt19937 eng(rd()); // Seed the generator

        // Define the range for digits (0-9)
        std::uniform_int_distribution<> distr(0, 9);

        std::string id;
        for (int i = 0; i < length; ++i)
        {
            id += std::to_string(distr(eng)); // Generate a random digit and append to the ID
        }

        return id;
    }
    void UIElement::build(Window *window)
    {
        useShader(shaderString.c_str(), window);
        float vertices[vert.size()];
        unsigned int indices[ind.size()];
        std::copy(vert.begin(), vert.end(), vertices);
        std::copy(ind.begin(), ind.end(), indices);
        glGenVertexArrays(1, &VAO);
        glGenBuffers(1, &VBO);
        glGenBuffers(1, &EBO);
        glBindVertexArray(VAO);
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, vert.size() * sizeof(float), vertices, GL_STATIC_DRAW);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, ind.size() * sizeof(unsigned int), indices, GL_STATIC_DRAW);
        int totalSize = 5;
        for (size_t i = 0; i < vertexAttributes.size(); i++)
        {
            totalSize += vertexAttributes[i].size;
        }
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, totalSize * sizeof(float), (void *)0); // Position
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, totalSize * sizeof(float), (void *)(3 * sizeof(float))); // Texture
        glEnableVertexAttribArray(1);
        int offset = 5;
        std::sort(vertexAttributes.begin(), vertexAttributes.end(),
                  [](const VertexAttribute &a, const VertexAttribute &b)
                  {
                      return a.location < b.location;
                  });

        for (size_t i = 0; i < vertexAttributes.size(); i++)
        {
            glVertexAttribPointer(vertexAttributes[i].location, vertexAttributes[i].size, GL_FLOAT, GL_FALSE, totalSize * sizeof(float), (void *)(offset * sizeof(float)));
            glEnableVertexAttribArray(vertexAttributes[i].location);
            offset += vertexAttributes[i].size;
        }
        glBindBuffer(GL_ARRAY_BUFFER, 0);
    }
    void UIElement::draw()
    {

        glBindTexture(GL_TEXTURE_2D, texture);
        if(!shader){
            handle_error("Shader is null. UiElement " + id);
        }
        shader->use();
        model_mat = glm::mat4(1.0f);
        model_mat = glm::translate(model_mat, glm::vec3(position.x, position.y, (float)ZIndex / 1000.0f));
        model_mat = glm::rotate(model_mat, glm::radians(180 + rotation), glm::vec3(0.0f, 0.0f, 1.0f));
        model_mat = glm::rotate(model_mat, glm::radians(180.0f), glm::vec3(0.0f, 1.0f, 0.0f));
        model_mat = glm::scale(model_mat, glm::vec3(scale.x, scale.y, 1.0f));
        shader->setMat4("model", model_mat);
        shader->setVec4("color", color);
        glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES, polCount, GL_UNSIGNED_INT, 0);
    }
}