#ifndef WINDOW_H
#define WINDOW_H
#include <glad/glad.h>
#include <GLFW/glfw3.h>
class Window {
public:
    Window(int width, int height, const char* title);
    int init();
    void start();
    void cleanup();
private:
    int width_;
    int height_;
    const char* title_;
    GLFWwindow *window;
};
#endif