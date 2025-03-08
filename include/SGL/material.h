#ifndef MATERIAL_H
#define MATERIAL_H
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
namespace SGL
{
    struct Material
    {
        glm::vec3 color;
        glm::vec3 ambient;
        glm::vec3 diffuse;
        glm::vec3 specular;
        float shininess;
        nlohmann::json toJson() const
        {
            nlohmann::json j;
            j["ambient"] = {ambient.x, ambient.y, ambient.z};
            j["diffuse"] = {diffuse.x, diffuse.y, diffuse.z};
            j["specular"] = {specular.x, specular.y, specular.z};
            j["shininess"] = shininess;
            return j;
        }

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
        void setColor(glm::vec3 color)
        {
            ambient = glm::vec3(color);
            diffuse = glm::vec3(color);
        }
    };
}
#endif