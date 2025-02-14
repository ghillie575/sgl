#ifndef CAMERA_H
#define CAMERA_H
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
namespace SGL{
class Camera
{
    private:
        glm::mat4 viewMatrix;
        glm::mat4 projectionMatrix;
    public:
        glm::vec2 position;
        glm::vec2 rotation;
        int zpos = -3;
        Camera();
        glm::mat4 getViewMatrix();
        glm::mat4 getProjectionMatrix() const;
        void setPosition(const glm::vec2 &position);
        void setRotation(const glm::vec2 &rotation);
        void setProjectionMatrix(const glm::mat4 &projectionMatrix);
        void setViewMatrix(const glm::mat4 &viewMatrix);
};
}
#endif // CAMERA_H