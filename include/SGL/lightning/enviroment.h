#ifndef ENVIROMENT_H
#define ENVIROMENT_H
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
namespace SGL::Lightning
{
    class Enviroment
    {
    public:
        float ambientStrenght;
        glm::vec3 sunPos;
        glm::vec3 sunColor;

        // Default constructor
        Enviroment()
            : ambientStrenght(0.1f), sunPos(glm::vec3(0, 0, 0)), sunColor(glm::vec3(1, 1, 1)) {}

        // Constructor with sun position
        Enviroment(glm::vec3 sunPos)
            : ambientStrenght(0.1f), sunPos(sunPos), sunColor(glm::vec3(1, 1, 1)) {}

        // Constructor with sun position and sun color
        Enviroment(glm::vec3 sunPos, glm::vec3 sunColor)
            : ambientStrenght(0.1f), sunPos(sunPos), sunColor(sunColor) {}

        // Constructor with all parameters
        Enviroment(float ambientStrenght, glm::vec3 sunPos, glm::vec3 sunColor)
            : ambientStrenght(ambientStrenght), sunPos(sunPos), sunColor(sunColor) {}
    };
}
#endif