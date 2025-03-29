#ifndef FREECAM_H
#define FREECAM_H
#include <SGL/window.h>
namespace SGL
{

    class FreeFlyCam
    {
    private:
        bool firstMouse = true;
        float yaw = -90.0f;
        float pitch = 0.0f;
        float lastX = 800.0f / 2.0;
        float lastY = 600.0 / 2.0;

    public:
        float camSpeed = 2.5f;
        bool photoMode = false;
        FreeFlyCam() {}
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
                float yoffset = lastY - ypos;
                lastX = xpos;
                lastY = ypos;

                float sensitivity = 0.1f;
                xoffset *= sensitivity;
                yoffset *= sensitivity;

                yaw += xoffset;
                pitch += yoffset;

                // Constrain pitch between -89 and 89 degrees
                if (pitch > 89.0f)
                    pitch = 89.0f;
                if (pitch < -89.0f)
                    pitch = -89.0f;

                // Convert to camera rotation (in degrees)
                window->camera.rotation.x = pitch;
                window->camera.rotation.y = yaw;

                // Keep y rotation between 0 and 360 degrees
                if (window->camera.rotation.y > 360.0f)
                    window->camera.rotation.y -= 360.0f;
                if (window->camera.rotation.y < 0.0f)
                    window->camera.rotation.y += 360.0f;
            }
        }
        void inputCallback(Window *window)
        {
            if (window->isKeyPressed(GLFW_KEY_W))
            {
                window->camera.moveForward(camSpeed * window->time.getDeltaTime());
            }
            if (window->isKeyPressed(GLFW_KEY_S))
            {
                window->camera.moveBackward(camSpeed * window->time.getDeltaTime());
            }
            if (window->isKeyPressed(GLFW_KEY_A))
            {
                window->camera.moveLeft(camSpeed * window->time.getDeltaTime());
            }
            if (window->isKeyPressed(GLFW_KEY_D))
            {
                window->camera.moveRight(camSpeed * window->time.getDeltaTime());
            }
        }
    };
}
#endif