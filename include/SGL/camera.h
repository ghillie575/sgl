#ifndef CAMERA_H
#define CAMERA_H
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
namespace SGL
{
    class Camera
    {
    private:
        glm::mat4 viewMatrix;
        glm::mat4 projectionMatrix;
        glm::vec3 cameraPos = glm::vec3(0.0f, 0.0f, 3.0f);
        glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
        glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);
    public:
        glm::vec3 position;
        glm::vec3 rotation;
        Camera();
        void moveForward(float speed);
        void moveBackward(float speed);
        void moveLeft(float speed);
        void moveRight(float speed);
        glm::mat4 getViewMatrix();
        glm::mat4 getProjectionMatrix() const;
        void setPosition(const glm::vec3 &position);
        void setRotation(const glm::vec3 &rotation);
        void setProjectionMatrix(const glm::mat4 &projectionMatrix);
        void setViewMatrix(const glm::mat4 &viewMatrix);
    };
}
#endif