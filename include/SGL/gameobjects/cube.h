#ifndef CUBE_H
#define CUBE_H

#include <SGL/object.h>
#include <SGL/logger.h>

namespace SGL::GameObjects{

/**
 * @brief A class representing a Cube game object.
 * 
 * This class inherits from the GameObject base class and provides
 * specific implementations for building and rendering a Cube object.
 */
class Cube : public GameObject
{
public:
    /**
     * @brief Builds the Cube object.
     * 
     * This method logs the building process and calls the base class
     * build method to perform any additional setup.
     */
    void build() override
    {
        Logger logger = Logger("Cube");
        logger.log(LogLevel::INFO, "Building Cube object");
        GameObject::build(); // Call the base class build method
    }

    /**
     * @brief Renders the Cube object.
     * 
     * This method calls the base class render method to handle rendering
     * the Cube object in the provided window.
     * 
     * @param window Pointer to the window where the Cube will be rendered.
     */
    void render(Window* window) override
    {
        GameObject::render(window); // Call the base class render method
    }
};

} // namespace SGL::GameObjects

#endif // CUBE_H
