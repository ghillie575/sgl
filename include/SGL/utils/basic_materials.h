#ifndef BASIC_MATERIALS_H

#include <SGL/material.h>

namespace SGL
{
    namespace Materials
    {
        Material emerald()
        {
            Material m;
            m.ambient = glm::vec3(0.0215f, 0.1745f, 0.0215f);
            m.diffuse = glm::vec3(0.07568f, 0.61424f, 0.07568f);
            m.specular = glm::vec3(0.633f, 0.727811f, 0.633f);
            m.shininess = 76.8f;
            return m;
        }

        Material jade()
        {
            Material m;
            m.ambient = glm::vec3(0.135f, 0.2225f, 0.1575f);
            m.diffuse = glm::vec3(0.54f, 0.89f, 0.63f);
            m.specular = glm::vec3(0.316228f, 0.316228f, 0.316228f);
            m.shininess = 12.8f;
            return m;
        }

        Material obsidian()
        {
            Material m;
            m.ambient = glm::vec3(0.05375f, 0.05f, 0.06625f);
            m.diffuse = glm::vec3(0.18275f, 0.17f, 0.22525f);
            m.specular = glm::vec3(0.332741f, 0.328634f, 0.346435f);
            m.shininess = 38.4f;
            return m;
        }

        Material pearl()
        {
            Material m;
            m.ambient = glm::vec3(0.25f, 0.20725f, 0.20725f);
            m.diffuse = glm::vec3(1.0f, 0.829f, 0.829f);
            m.specular = glm::vec3(0.296648f, 0.296648f, 0.296648f);
            m.shininess = 11.264f;
            return m;
        }

        Material plastic()
        {
            Material m;
            m.ambient = glm::vec3(0.1745f, 0.01175f, 0.01175f);
            m.diffuse = glm::vec3(0.61424f, 0.04136f, 0.04136f);
            m.specular = glm::vec3(0.727811f, 0.626959f, 0.626959f);
            m.shininess = 76.8f;
            return m;
        }

        Material turquoise()
        {
            Material m;
            m.ambient = glm::vec3(0.1f, 0.18725f, 0.1745f);
            m.diffuse = glm::vec3(0.396f, 0.74151f, 0.69102f);
            m.specular = glm::vec3(0.297254f, 0.30829f, 0.306678f);
            m.shininess = 12.8f;
            return m;
        }

        Material brass()
        {
            Material m;
            m.ambient = glm::vec3(0.329412f, 0.223529f, 0.027451f);
            m.diffuse = glm::vec3(0.780392f, 0.568627f, 0.113725f);
            m.specular = glm::vec3(0.992157f, 0.941176f, 0.807843f);
            m.shininess = 27.8974f;
            return m;
        }

        Material bronze()
        {
            Material m;
            m.ambient = glm::vec3(0.2125f, 0.1275f, 0.054f);
            m.diffuse = glm::vec3(0.714f, 0.4284f, 0.18144f);
            m.specular = glm::vec3(0.393548f, 0.271906f, 0.166721f);
            m.shininess = 25.6f;
            return m;
        }

        Material chrome()
        {
            Material m;
            m.ambient = glm::vec3(0.25f, 0.25f, 0.25f);
            m.diffuse = glm::vec3(0.4f, 0.4f, 0.4f);
            m.specular = glm::vec3(0.774597f, 0.774597f, 0.774597f);
            m.shininess = 76.8f;
            return m;
        }

        Material gold()
        {
            Material m;
            m.ambient = glm::vec3(0.24725f, 0.1995f, 0.0745f);
            m.diffuse = glm::vec3(0.75164f, 0.60648f, 0.22648f);
            m.specular = glm::vec3(0.628281f, 0.555802f, 0.366065f);
            m.shininess = 51.2f;
            return m;
        }

        Material silver()
        {
            Material m;
            m.ambient = glm::vec3(0.19225f, 0.19225f, 0.19225f);
            m.diffuse = glm::vec3(0.50754f, 0.50754f, 0.50754f);
            m.specular = glm::vec3(0.508273f, 0.508273f, 0.508273f);
            m.shininess = 51.2f;
            return m;
        }

        Material copper()
        {
            Material m;
            m.ambient = glm::vec3(0.19125f, 0.0735f, 0.0225f);
            m.diffuse = glm::vec3(0.7038f, 0.27048f, 0.0828f);
            m.specular = glm::vec3(0.256777f, 0.137622f, 0.086014f);
            m.shininess = 12.8f;
            return m;
        }

        Material aluminum()
        {
            Material m;
            m.ambient = glm::vec3(0.24725f, 0.24725f, 0.24725f);
            m.diffuse = glm::vec3(0.8f, 0.8f, 0.8f);
            m.specular = glm::vec3(0.774597f, 0.774597f, 0.774597f);
            m.shininess = 50.0f;
            return m;
        }

    }
}
#define BASIC_MATERIALS_H
#endif // BASIC_MATERIALS_H