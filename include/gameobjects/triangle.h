#ifndef TRIANGLE_H
#define TRIANGLE_H

#include <object.h>

#include <logger.h>

class Triangle : public GameObject
{
public:
    void build() override
    {
        Logger logger = Logger("Triangle");
        logger.log(LogLevel::INFO, "Building Triangle object");
        GameObject::build(); // Call the base class build method
    }
};


#endif // TRIANGLE_H
