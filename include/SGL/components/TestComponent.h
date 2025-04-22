#ifndef TESTCOMPONENT_H
#define TESTCOMPONENT_H

#include <SGL/component.h>

namespace SGL::Components {

/**
 * @brief A test component class that inherits from the base Component class.
 * 
 * This component is used for demonstration purposes. It overrides the Start
 * and Update methods to provide specific functionality.
 */
class TestComponent : public Component
{
public:
    /**
     * @brief Constructor for TestComponent.
     * 
     * Initializes the component with the name "TestComponent".
     */
    TestComponent() : Component("TestComponent") {}

    /**
     * @brief Called when the component is started.
     * 
     * Logs a message indicating that the TestComponent has started.
     */
    void Start() override {
        logger.log(LogLevel::INFO, "Start TestComponent");
    }

    /**
     * @brief Called every frame to update the component.
     * 
     * Rotates the transform of the component based on the elapsed time.
     */
    void Update() override {
        transform->setRotation(glm::vec3((float)glfwGetTime() * glm::radians(50.0f) * 70));
    }   
};

} // namespace SGL::Components

#endif // TESTCOMPONENT_H
