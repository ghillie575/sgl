#ifndef FREECAM_H
#define FREECAM_H

#include <SGL/window.h>

namespace SGL
{
    /**
     * @brief A class representing a free-fly camera system.
     * 
     * This class provides functionality for controlling a camera in a 3D environment
     * using mouse and keyboard inputs. It supports movement in all directions and
     * rotation based on mouse movement.
     */
    class FreeFlyCam
    {
    private:
        bool firstMouse = true; ///< Tracks if the mouse is being used for the first time.
        float yaw = -90.0f;     ///< Horizontal rotation angle of the camera.
        float pitch = 0.0f;     ///< Vertical rotation angle of the camera.
        float lastX = 800.0f / 2.0; ///< Last recorded X position of the mouse.
        float lastY = 600.0 / 2.0;  ///< Last recorded Y position of the mouse.

    public:
        float camSpeed = 2.5f;  ///< Speed of the camera movement.
        bool photoMode = false; ///< If true, disables camera movement.

        /**
         * @brief Default constructor for FreeFlyCam.
         */
        FreeFlyCam() {}

        /**
         * @brief Handles mouse movement to rotate the camera.
         * 
         * @param window Pointer to the window object.
         * @param xpos Current X position of the mouse.
         * @param ypos Current Y position of the mouse.
         */
        void mouseCallback(Window *window, double xpos, double ypos)
        {
            if (!photoMode)
            {
                if (firstMouse)
                {
                    lastX = xpos;
                    lastY = ypos;
                    firstMouse = false;
                }

                float xoffset = xpos - lastX;
                float yoffset = lastY - ypos; // Reversed since y-coordinates go from bottom to top.
                lastX = xpos;
                lastY = ypos;

                float sensitivity = 0.1f; // Sensitivity of mouse movement.
                xoffset *= sensitivity;
                yoffset *= sensitivity;

                yaw += xoffset;
                pitch += yoffset;

                // Constrain pitch between -89 and 89 degrees to prevent flipping.
                if (pitch > 89.0f)
                    pitch = 89.0f;
                if (pitch < -89.0f)
                    pitch = -89.0f;

                // Update camera rotation based on yaw and pitch.
                window->camera.rotation.x = pitch;
                window->camera.rotation.y = yaw;

                // Keep yaw (y rotation) within 0 to 360 degrees.
                if (window->camera.rotation.y > 360.0f)
                    window->camera.rotation.y -= 360.0f;
                if (window->camera.rotation.y < 0.0f)
                    window->camera.rotation.y += 360.0f;
            }
        }

        /**
         * @brief Handles keyboard input to move the camera.
         * 
         * @param window Pointer to the window object.
         */
        void inputCallback(Window *window)
        {
            if (window->isKeyPressed(GLFW_KEY_W))
            {
                // Move the camera forward.
                window->camera.moveForward(camSpeed * window->time.getDeltaTime());
            }
            if (window->isKeyPressed(GLFW_KEY_S))
            {
                // Move the camera backward.
                window->camera.moveBackward(camSpeed * window->time.getDeltaTime());
            }
            if (window->isKeyPressed(GLFW_KEY_A))
            {
                // Move the camera to the left.
                window->camera.moveLeft(camSpeed * window->time.getDeltaTime());
            }
            if (window->isKeyPressed(GLFW_KEY_D))
            {
                // Move the camera to the right.
                window->camera.moveRight(camSpeed * window->time.getDeltaTime());
            }
        }
    };
}

#endif