#include <nlohmann/json.hpp>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <SGL/window.h>
#ifndef TRANSFORM_H
#define TRANSFORM_H
namespace SGL{
class Transform
{
public:
    Transform() : position(0.0f), rotation(0.0f), scaling(1.0f) {}

    glm::vec2 position = glm::vec2(0, 0);
    glm::vec2 rotation = glm::vec2(0, 0);
    glm::vec2 scaling = glm::vec2(1, 1);
    float zindex = 0;
    void setPosition(const glm::vec2 &position);
    void setRotation(const glm::vec2 &rotation);
    void setScaling(const glm::vec2 &scaling);

    glm::vec2 getPosition() const;
    glm::vec2 getRotation() const;
    glm::vec2 getScaling() const;

    void translate(const glm::vec2 &translation);
    void rotate(const glm::vec2 &rotation);
    void scale(const glm::vec2 &scale);

    glm::mat4 getTransformationMatrix() const;

    nlohmann::json toJson() const;
    void fromJson(const nlohmann::json &json);
};
}
#endif