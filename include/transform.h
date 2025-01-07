#include <nlohmann/json.hpp>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <window.h>
#ifndef TRANSFORM_H
#define TRANSFORM_H
class Transform
{
public:
    Transform() : position(0.0f), rotation(0.0f), scaling(1.0f) {}

    glm::vec3 position = glm::vec3(0, 0, 0);
    glm::vec3 rotation = glm::vec3(0, 0, 0);
    glm::vec3 scaling = glm::vec3(1, 1, 1);

    void setPosition(const glm::vec3 &position);
    void setRotation(const glm::vec3 &rotation);
    void setScaling(const glm::vec3 &scaling);

    glm::vec3 getPosition() const;
    glm::vec3 getRotation() const;
    glm::vec3 getScaling() const;

    void translate(const glm::vec3 &translation);
    void rotate(const glm::vec3 &rotation);
    void scale(const glm::vec3 &scale);

    glm::mat4 getTransformationMatrix() const;

    nlohmann::json toJson() const;
    void fromJson(const nlohmann::json &json);
};

#endif