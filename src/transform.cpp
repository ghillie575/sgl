#include <transform.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <nlohmann/json.hpp>

using json = nlohmann::json;
glm::mat4 Transform::getTransformationMatrix() const
{
    glm::mat4 transformationMatrix = glm::mat4(1.0f);
    transformationMatrix = glm::translate(transformationMatrix, position);
    transformationMatrix = glm::rotate(transformationMatrix, glm::radians(rotation.x), glm::vec3(1.0f, 0.0f, 0.0f));
    transformationMatrix = glm::rotate(transformationMatrix, glm::radians(rotation.y), glm::vec3(0.0f, 1.0f, 0.0f));
    transformationMatrix = glm::rotate(transformationMatrix, glm::radians(rotation.z), glm::vec3(0.0f, 0.0f, 1.0f));
    transformationMatrix = glm::scale(transformationMatrix, scaling);
    return transformationMatrix;
}
void Transform::setPosition(const glm::vec3 &position) { this->position = position; }
void Transform::setRotation(const glm::vec3 &rotation) { this->rotation = rotation; }
void Transform::setScaling(const glm::vec3 &scale) { this->scaling = scale; }

glm::vec3 Transform::getPosition() const { return position; }
glm::vec3 Transform::getRotation() const { return rotation; }
glm::vec3 Transform::getScaling() const { return scaling; }

void Transform::translate(const glm::vec3 &translation) { position += translation; }
void Transform::rotate(const glm::vec3 &rotation) { this->rotation += rotation; }
void Transform::scale(const glm::vec3 &scale) { this->scaling *= scale; }
nlohmann::json Transform::toJson() const{
    nlohmann::json jsonData;
    jsonData["position"] = { position.x, position.y, position.z };
    jsonData["rotation"] = { rotation.x, rotation.y, rotation.z };
    jsonData["scaling"] = { scaling.x, scaling.y, scaling.z };
    return jsonData;
}

void Transform::fromJson(const nlohmann::json &json) {
    if (json.contains("position")) {
        position = glm::vec3(json["position"][0], json["position"][1], json["position"][2]);
    }
    if (json.contains("rotation")) {
        rotation = glm::vec3(json["rotation"][0], json["rotation"][1], json["rotation"][2]);
    }
    if (json.contains("scaling")) {
        scaling = glm::vec3(json["scaling"][0], json["scaling"][1], json["scaling"][2]);
    }
}

