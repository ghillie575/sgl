#ifndef CAMERA_H
#define CAMERA_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

namespace SGL
{
    /**
     * @brief A class representing a 3D camera for rendering scenes.
     * Provides functionality for camera movement, rotation, and projection/view matrix management.
     */
    class Camera
    {
    private:
        glm::mat4 viewMatrix;          ///< The view matrix representing the camera's orientation and position.
        glm::mat4 projectionMatrix;    ///< The projection matrix for perspective or orthographic projection.

        glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f); ///< The up vector of the camera.

    public:
        float fov = 45.0f;             ///< Field of view (FOV) in degrees.
        glm::vec3 cameraPos = glm::vec3(0.0f, 0.0f, 3.0f); ///< The position of the camera in world space.
        glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f); ///< The direction the camera is facing.
        glm::vec3 rotation;           ///< The rotation of the camera (pitch, yaw, roll).

        /**
         * @brief Default constructor for the Camera class.
         */
        Camera();

        /**
         * @brief Moves the camera forward along the camera's front vector.
         * @param speed The speed of the movement.
         */
        void moveForward(float speed);

        /**
         * @brief Moves the camera backward along the camera's front vector.
         * @param speed The speed of the movement.
         */
        void moveBackward(float speed);

        /**
         * @brief Updates the camera's direction vectors based on its rotation.
         */
        void updateCameraVectors();

        /**
         * @brief Moves the camera to the left, perpendicular to the front vector.
         * @param speed The speed of the movement.
         */
        void moveLeft(float speed);

        /**
         * @brief Moves the camera to the right, perpendicular to the front vector.
         * @param speed The speed of the movement.
         */
        void moveRight(float speed);

        /**
         * @brief Retrieves the current view matrix of the camera.
         * @return The view matrix.
         */
        glm::mat4 getViewMatrix();

        /**
         * @brief Retrieves the current projection matrix of the camera.
         * @return The projection matrix.
         */
        glm::mat4 getProjectionMatrix() const;

        /**
         * @brief Sets the position of the camera.
         * @param position The new position of the camera.
         */
        void setPosition(const glm::vec3 &position);

        /**
         * @brief Sets the rotation of the camera.
         * @param rotation The new rotation of the camera (pitch, yaw, roll).
         */
        void setRotation(const glm::vec3 &rotation);

        /**
         * @brief Sets the projection matrix of the camera.
         * @param projectionMatrix The new projection matrix.
         */
        void setProjectionMatrix(const glm::mat4 &projectionMatrix);

        /**
         * @brief Sets the view matrix of the camera.
         * @param viewMatrix The new view matrix.
         */
        void setViewMatrix(const glm::mat4 &viewMatrix);
    };
}

#endif