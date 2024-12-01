#include <transform.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
glm::mat4 Transform::getTransformationMatrix() const
{
    glm::mat4 translationMatrix = glm::translate(glm::mat4(1.0f), position);
    glm::mat4 rotationMatrix = glm::rotate(glm::mat4(1.0f), glm::radians(rotation.x), glm::vec3(1.0f, 0.0f, 0.0f));
    rotationMatrix = glm::rotate(rotationMatrix, glm::radians(rotation.y), glm::vec3(0.0f, 1.0f, 0.0f));
    rotationMatrix = glm::rotate(rotationMatrix, glm::radians(rotation.z), glm::vec3(0.0f, 0.0f, 1.0f));
    glm::mat4 scaleMatrix = glm::scale(glm::mat4(1.0f), scaling);
    return translationMatrix * rotationMatrix * scaleMatrix;
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
