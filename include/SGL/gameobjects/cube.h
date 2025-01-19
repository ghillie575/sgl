#ifndef CUBE_H
#define CUBE_H

#include <SGL/object.h>

#include <SGL/logger.h>

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
        
        GameObject::render(); // Call the base class render method
    }
};


#endif // TRIANGLE_H
