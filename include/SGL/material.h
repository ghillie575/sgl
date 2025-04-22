#ifndef MATERIAL_H
#define MATERIAL_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <nlohmann/json.hpp> // For JSON serialization/deserialization

namespace SGL
{
    /**
     * @brief Represents a material with properties for rendering.
     * 
     * The Material struct contains properties such as color, ambient, diffuse, 
     * specular, and shininess, which are commonly used in lighting calculations 
     * for 3D rendering. It also provides methods for JSON serialization and 
     * deserialization, as well as utility functions to set the material's color.
     */
    struct Material
    {
        glm::vec3 color;      ///< Base color of the material (not used in lighting calculations).
        glm::vec3 ambient;    ///< Ambient reflection coefficient.
        glm::vec3 diffuse;    ///< Diffuse reflection coefficient.
        glm::vec3 specular;   ///< Specular reflection coefficient.
        float shininess;      ///< Shininess factor for specular highlights.

        /**
         * @brief Serializes the material properties to a JSON object.
         * 
         * @return nlohmann::json A JSON object representing the material properties.
         */
        nlohmann::json toJson() const
        {
            nlohmann::json j;
            j["ambient"] = {ambient.x, ambient.y, ambient.z};
            j["diffuse"] = {diffuse.x, diffuse.y, diffuse.z};
            j["specular"] = {specular.x, specular.y, specular.z};
            j["shininess"] = shininess;
            return j;
        }

        /**
         * @brief Deserializes the material properties from a JSON object.
         * 
         * @param j A JSON object containing the material properties.
         */
        void fromJson(const nlohmann::json &j)
        {
            if (j.contains("ambient") && j["ambient"].is_array() && j["ambient"].size() == 3)
            {
                ambient = glm::vec3(j["ambient"][0], j["ambient"][1], j["ambient"][2]);
            }
            if (j.contains("diffuse") && j["diffuse"].is_array() && j["diffuse"].size() == 3)
            {
                diffuse = glm::vec3(j["diffuse"][0], j["diffuse"][1], j["diffuse"][2]);
            }
            if (j.contains("specular") && j["specular"].is_array() && j["specular"].size() == 3)
            {
                specular = glm::vec3(j["specular"][0], j["specular"][1], j["specular"][2]);
            }
            if (j.contains("shininess") && j["shininess"].is_number())
            {
                shininess = j["shininess"];
            }
        }

        /**
         * @brief Sets the material's ambient and diffuse properties based on a color.
         * 
         * @param color A glm::vec3 representing the color.
         */
        void setColor(glm::vec3 color)
        {
            ambient = color * 0.7f; // Ambient is 70% of the base color.
            diffuse = color;       // Diffuse is the base color.
        }

        /**
         * @brief Sets the material's ambient and diffuse properties based on RGB values.
         * 
         * @param r Red component (0-255).
         * @param g Green component (0-255).
         * @param b Blue component (0-255).
         */
        void setColor(float r, float g, float b)
        {
            ambient = glm::vec3(r / 255, g / 255, b / 255) * 0.7f; // Ambient is 70% of the base color.
            diffuse = glm::vec3(r / 255, g / 255, b / 255);        // Diffuse is the base color.
        }
    };
}

#endif