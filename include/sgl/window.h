#ifndef WINDOW_H
#define WINDOW_H
#include <string>
#include <GLFW/glfw3.h>
#include <sgl/logger.h>
class SGLWindow
{
private:
    bool debuggerEnabled = false;
    std::string title;
    int width;
    int height;
    GLFWwindow *window;
    Logger logger = Logger("Window");
public:
    SGLWindow(std::string title, int width, int height) : title(title), width(width), height(height) {}
    SGLWindow(std::string title, int width, int height, bool debug) : title(title), width(width), height(height), debuggerEnabled(debug) {}
    void init();
    void start();
    static void glfw_errorCallback(int error, const char *description);
    static void glfw_keyCallback(GLFWwindow *window, int key, int scancode, int action, int mods);
};
#endif