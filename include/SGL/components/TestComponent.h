#ifndef TESTCOMPONENT_H
#define TESTCOMPONENT_H

#include <SGL/component.h>
namespace SGL::Components{
class TestComponent : public Component
{
public:
	TestComponent() : Component("TestComponent") {}
    void Start() override {
        logger.log(LogLevel::INFO, "Start TestComponent");
    }
    void Update() override {
        transform->setRotation(glm::vec3((float)glfwGetTime() * glm::radians(50.0f) * 70));
    }   
};
}
#endif // TESTCOMPONENT_H
