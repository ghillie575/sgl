#ifndef LIGHTNING_DEBUG_H
#define LIGHTNING_DEBUG_H

#include <SGL/window.h>

namespace SGL{

    /**
     * @brief Visualizes the light source in the scene.
     * 
     * This function creates a simple 3D cube object to represent the light source
     * in the scene. The cube is positioned at the light source's position, scaled
     * down, and rendered using a specific shader. The object is registered to the
     * window for rendering, but its physics processing is disabled.
     * 
     * @param window Pointer to the Window object where the light source will be visualized.
     */
    void visualizeLightSource(Window* window){
        // Create a new game object using the factory with a default configuration
        std::shared_ptr<GameObject> obj = window->factory.createObject("default");

        // Use the "light" shader for rendering the object
        obj->useShader("light");

        // Load a basic 3D cube model to represent the light source
        obj->loadModel("basic/3d/cube");

        // Set the position of the object to match the light source's position
        obj->transform.setPosition(window->lightEnv.sunPos);

        // Scale the object down to make it smaller
        obj->transform.setScaling(glm::vec3(0.3, 0.3, 0.3));

        // Disable physics processing for the object
        obj->physObject->processPhysics = false;

        // Register the object to the window for rendering
        window->registerObject(obj);
    }
}

#endif