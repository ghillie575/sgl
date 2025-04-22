#ifndef ENVIROMENT_H
#define ENVIROMENT_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

namespace SGL::Lightning
{
    /**
     * @brief Represents the environment settings for lighting in a scene.
     */
    class Enviroment
    {
    public:
        float ambientStrenght; ///< Strength of ambient lighting.
        glm::vec3 sunPos;      ///< Position of the sun in the scene.
        glm::vec3 sunColor;    ///< Color of the sunlight.

        /**
         * @brief Default constructor.
         * Initializes the environment with default values.
         */
        Enviroment()
            : ambientStrenght(0.1f), sunPos(glm::vec3(0, 0, 0)), sunColor(glm::vec3(1, 1, 1)) {}

        /**
         * @brief Constructor with sun position.
         * @param sunPos Position of the sun.
         */
        Enviroment(glm::vec3 sunPos)
            : ambientStrenght(0.1f), sunPos(sunPos), sunColor(glm::vec3(1, 1, 1)) {}

        /**
         * @brief Constructor with sun position and sun color.
         * @param sunPos Position of the sun.
         * @param sunColor Color of the sunlight.
         */
        Enviroment(glm::vec3 sunPos, glm::vec3 sunColor)
            : ambientStrenght(0.1f), sunPos(sunPos), sunColor(sunColor) {}

        /**
         * @brief Constructor with all parameters.
         * @param ambientStrenght Strength of ambient lighting.
         * @param sunPos Position of the sun.
         * @param sunColor Color of the sunlight.
         */
        Enviroment(float ambientStrenght, glm::vec3 sunPos, glm::vec3 sunColor)
            : ambientStrenght(ambientStrenght), sunPos(sunPos), sunColor(sunColor) {}
    };
}

#endif