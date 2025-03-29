#ifndef COLORCHANGE_H
#define COLORCHANGE_H
#include <SGL/component.h>
namespace SGL::Components
{
    class ColorChangeComponent : public Component
    {
        private:
        glm::vec3 color;
    public:
        ColorChangeComponent() : Component("ColorChanger") {}
        void Start() override
        {
            logger.log(LogLevel::INFO, "Start TestComponent");
        }
        void Update() override
        {
            float time = glfwGetTime() * 0.1f;  // Get the current time

            gameObject->material.ambient.r = 0.5f * (sin(time) + 1.0f); // Smoothly vary between 0 and 1
            gameObject->material.ambient.g = 0.5f * (sin(time + 2.0f) + 1.0f); // Offset the green channel
            gameObject->material.ambient.b = 0.5f * (sin(time + 4.0f) + 1.0f); // Offset the blue channel
        
            gameObject->material.diffuse = gameObject->material.ambient; // For simplicity, let's apply the same cycling to diffuse
        }
    };
}
#endif // TESTCOMPONENT_H
