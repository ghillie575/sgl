#ifndef COLORCHANGE_H
#define COLORCHANGE_H

#include <SGL/component.h>

namespace SGL::Components
{
    /**
     * @brief A component that smoothly changes the color of a GameObject's material over time.
     * 
     * This component modifies the ambient and diffuse properties of the GameObject's material
     * to create a color-cycling effect. The color changes are based on the sine function, 
     * creating a smooth transition between colors.
     */
    class ColorChangeComponent : public Component
    {
    private:
        glm::vec3 color; ///< Placeholder for color data (not currently used).

    public:
        /**
         * @brief Constructor for the ColorChangeComponent.
         * 
         * Initializes the component with the name "ColorChanger".
         */
        ColorChangeComponent() : Component("ColorChanger") {}

        /**
         * @brief Called when the component is first initialized.
         * 
         * Logs a message indicating that the component has started.
         */
        void Start() override
        {
            logger.log(LogLevel::INFO, "Start TestComponent");
        }

        /**
         * @brief Called every frame to update the component's behavior.
         * 
         * Smoothly varies the ambient and diffuse colors of the GameObject's material
         * over time using sine wave calculations.
         */
        void Update() override
        {
            float time = glfwGetTime() * 0.1f;  // Get the current time and scale it down.

            // Smoothly vary the red, green, and blue channels of the ambient color.
            gameObject->material.ambient.r = 0.5f * (sin(time) + 1.0f); // Red channel
            gameObject->material.ambient.g = 0.5f * (sin(time + 2.0f) + 1.0f); // Green channel (offset)
            gameObject->material.ambient.b = 0.5f * (sin(time + 4.0f) + 1.0f); // Blue channel (offset)
        
            // Apply the same color cycling to the diffuse property for simplicity.
            gameObject->material.diffuse = gameObject->material.ambient;
        }
    };
}

#endif // COLORCHANGE_H
