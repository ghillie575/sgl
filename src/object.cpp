#include <SGL/object.h>
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
#define STB_IMAGE_IMPLEMENTATION
#include <stbi/stb_image.h>
using namespace SGL;
GameObject::GameObject()
{
    this->transform.setScaling(glm::vec3(1, 1, 1));
    this->id = generateRandomID(10);
    this->logger = Logger("", debug);
    this->physObject = new PhysObject();
}
void GameObject::loadModel(std::string modelName)
{
    // Load vertices from .vmodel file
    std::string path = "engine/models/" + modelName + ".vmodel";
    std::ifstream file(path);
    if (!file.is_open())
    {
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
    int totalSize = 8;
    for (size_t i = 0; i < vertexAttributes.size(); i++)
    {
        totalSize += vertexAttributes[i].size;
    }

    // Check if the number of values is a multiple of 8 (3 for vertex + 2 for texture coordinates + 3 for normals) + vertex attributes
    if (vert.size() % totalSize != 0)
    {
        throw std::runtime_error("Invalid .vmodel file format: Incorrect number of values.");
    }

    // Load indices from .imodel file
    path = "engine/models/" + modelName + ".imodel";
    std::ifstream file1(path);
    if (!file1.is_open())
    {
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

    // Calculate the number of polygons
    polCount = ind.size();

    printModelData();
}
void GameObject::setColor(glm::vec4 color)
{
    this->color = color;
}
void GameObject::printModelData()
{
    std::ostringstream oss; // Use ostringstream to build the string

    oss << "Vertices and Texture Coordinates for object: " << id << "\n";
    for (size_t i = 0; i < vert.size(); i += 5)
    {
        oss << "Vertex \e[91m" << (i / 5) + 1 << "\e[0m: "
            << "\e[35mPosition\e[0m(\e[92m" << vert[i] << " " << vert[i + 1] << " " << vert[i + 2] << "\e[0m) \e[0m"
            << "\e[96mTexture\e[0m(\e[92m" << vert[i + 3] << " " << vert[i + 4] << "\e[0m)\e[0m\n";
    }

    oss << "\nIndices:\n";
    for (size_t i = 0; i < ind.size(); ++i)
    {
        oss << ind[i] << (i < ind.size() - 1 ? ", " : "\n");
    }

    oss << "Number of Polygons: " << polCount << "\n";
    logger.log(LogLevel::DEBUG, oss.str());
}
void GameObject::useTexture(std::string texturePath)
{
    if (!std::ifstream("engine/textures/" + texturePath))
    {
        logger.log(LogLevel::ERROR, "Texture file does not exist: " + texturePath);
        useTexture("blank.jpg");
        return;
    }
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
    }
    stbi_image_free(data);
}
void GameObject::build()
{

    float vertices[vert.size()];
    unsigned int indices[ind.size()];
    std::copy(vert.begin(), vert.end(), vertices);
    std::copy(ind.begin(), ind.end(), indices);
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    if (modelUsesEBO)
    {
        glGenBuffers(1, &EBO);
    }

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, vert.size() * sizeof(float), vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, ind.size() * sizeof(unsigned int), indices, GL_STATIC_DRAW);
    int totalSize = 8;
    for (size_t i = 0; i < vertexAttributes.size(); i++)
    {
        totalSize += vertexAttributes[i].size;
    }
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, totalSize * sizeof(float), (void *)0); // Position
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, totalSize * sizeof(float), (void *)(3 * sizeof(float))); // Texture
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, totalSize * sizeof(float), (void *)(5 * sizeof(float))); // Normals
    glEnableVertexAttribArray(2);
    int offset = 8;
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

void GameObject::useShader(const char *shaderName)
{
    this->shaderName = shaderName;
}
void GameObject::useShader(Shader *shader)
{
    this->shader = shader;
}
std::string GameObject::generateRandomID(int length)
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
void GameObject::start(Window *window)
{
    for (size_t i = 0; i < components.size(); i++)
    {
        components[i]->gameObject = this;
        components[i]->transform = &transform;
        components[i]->prepare();
    }

    for (size_t i = 0; i < components.size(); i++)
    {
        components[i]->Start();
    }
    physObject->setup(window);
}
void GameObject::render(Window *window)
{
    glBindTexture(GL_TEXTURE_2D, texture);
    if (physObject->processPhysics)
    {
        physx::PxTransform physTransform = physObject->actor->getGlobalPose();
        transform.setPosition(glm::vec3(physTransform.p.x, physTransform.p.y, physTransform.p.z));
        PxQuat pxQ = physTransform.q;
        glm::quat q(pxQ.w, pxQ.x, pxQ.y, pxQ.z); // GLM uses (w, x, y, z)

        glm::vec3 eulerRad = glm::eulerAngles(q);
        glm::vec3 eulerDeg = glm::degrees(eulerRad); // Optional
        transform.setRotation(eulerDeg);
    }

    glm::mat4 model = transform.getTransformationMatrix();
    shader->use();
    setColor(color);
    shader->setVec3("camPos", window->camera.cameraPos);
    shader->setVec3("material.ambient", material.ambient);
    shader->setVec3("material.diffuse", material.diffuse);
    shader->setVec3("material.specular", material.specular);
    shader->setFloat("material.shininess", material.shininess);
    shader->setMat4("model", model);
    shader->setMat4("view", window->camera.getViewMatrix());
    glBindVertexArray(VAO);
    for (size_t i = 0; i < components.size(); i++)
    {
        components[i]->Update();
    }
    glDrawElements(GL_TRIANGLES, polCount, GL_UNSIGNED_INT, 0);
}
void GameObject::freeResources()
{
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
}
void GameObject::addComponent(Window *window, std::string type)
{
    std::shared_ptr<Component> objc = window->factory.createComponent(type);
    components.push_back(objc);
}
void GameObject::debugger()
{
    logger = Logger("GameObject", debug);
}