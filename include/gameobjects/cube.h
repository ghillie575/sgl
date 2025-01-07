#ifndef TRIANGLE_H
#define TRIANGLE_H

#include <object.h>

#include <logger.h>

class Cube : public GameObject
{
public:
    void build() override
    {
        Logger logger = Logger("Cube");
        logger.log(LogLevel::INFO, "Building Cube object");
        GameObject::build(); // Call the base class build method
    }
    void render() override
    {
        transform.setRotation(glm::vec3((float)glfwGetTime() * glm::radians(50.0f) * 50));
        GameObject::render(); // Call the base class render method
    }
};


#endif // TRIANGLE_H
