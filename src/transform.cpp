#include <SGL/transform.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <nlohmann/json.hpp>
using namespace SGL;
using json = nlohmann::json;
glm::mat4 Transform::getTransformationMatrix() const
{
    glm::mat4 transformationMatrix = glm::mat4(1.0f);
    transformationMatrix = glm::translate(transformationMatrix, glm::vec3(position,zindex / 100));
    transformationMatrix = glm::rotate(transformationMatrix, glm::radians(rotation.x), glm::vec3(1.0f, 0.0f, 0.0f));
    transformationMatrix = glm::rotate(transformationMatrix, glm::radians(rotation.y), glm::vec3(0.0f, 1.0f, 0.0f));
    transformationMatrix = glm::scale(transformationMatrix, glm::vec3(scaling,0));
    return transformationMatrix;
}
void Transform::setPosition(const glm::vec2 &position) { this->position = position; }
void Transform::setRotation(const glm::vec2 &rotation) { this->rotation = rotation; }
void Transform::setScaling(const glm::vec2 &scale) { this->scaling = scale; }

glm::vec2 Transform::getPosition() const { return position; }
glm::vec2 Transform::getRotation() const { return rotation; }
glm::vec2 Transform::getScaling() const { return scaling; }

void Transform::translate(const glm::vec2 &translation) { position += translation; }
void Transform::rotate(const glm::vec2 &rotation) { this->rotation += rotation; }
void Transform::scale(const glm::vec2 &scale) { this->scaling *= scale; }
nlohmann::json Transform::toJson() const{
    nlohmann::json jsonData;
    jsonData["position"] = { position.x, position.y, zindex};
    jsonData["rotation"] = { rotation.x, rotation.y};
    jsonData["scaling"] = { scaling.x, scaling.y};
    return jsonData;
}

void Transform::fromJson(const nlohmann::json &json) {
    if (json.contains("position")) {this->rotation += rotation;
        position = glm::vec2(json["position"][0], json["position"][1]);
        zindex = json["position"][2];
    }
    if (json.contains("rotation")) {
        rotation = glm::vec2(json["rotation"][0], json["rotation"][1]);
    }
    if (json.contains("scaling")) {
        scaling = glm::vec2(json["scaling"][0], json["scaling"][1]);
    }
}

