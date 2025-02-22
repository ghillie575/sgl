#include <SGL/camera.h>
using namespace SGL;

/**
 * @brief Constructs a Camera object with default position, rotation, 
 * view matrix, and projection matrix.
 *
 * Initializes the camera's position and rotation to zero vectors,
 * and the view and projection matrices to identity matrices.
 */

Camera::Camera()
{
    position = glm::vec3(0.0f);
    rotation = glm::vec3(0.0f);
    viewMatrix = glm::mat4(1.0f);
    projectionMatrix = glm::mat4(1.0f);
}

glm::mat4 Camera::getViewMatrix() { 
    viewMatrix = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);
    return viewMatrix; 
}
glm::mat4 Camera::getProjectionMatrix() const { return projectionMatrix; }

void Camera::setPosition(const glm::vec3 &position) { this->position = position; }
void Camera::setRotation(const glm::vec3 &rotation) { this->rotation = rotation; }
void Camera::setProjectionMatrix(const glm::mat4 &projectionMatrix) { this->projectionMatrix = projectionMatrix; }
void Camera::setViewMatrix(const glm::mat4 &viewMatrix) { 
    this->viewMatrix = viewMatrix;
 }
 void Camera::moveForward(float speed) {
    cameraPos += speed * cameraFront;
}
void Camera::moveBackward(float speed) {
    cameraPos -= speed * cameraFront;
}
void Camera::moveLeft(float speed) {
    cameraPos -= glm::normalize(glm::cross(cameraFront, cameraUp)) * speed;
}
void Camera::moveRight(float speed) {
    cameraPos += glm::normalize(glm::cross(cameraFront, cameraUp)) * speed;
}