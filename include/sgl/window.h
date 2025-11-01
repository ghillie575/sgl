#ifndef WINDOW_H
#define WINDOW_H
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <functional>
class Window
{
public:
    Window(int width, int height, const char *title);
    int init();
    void start();
    void cleanup();
    bool isRunning();
    void setFpsLimit(int fps);
    double getDeltaTime()
    {
        return deltaTime;
    }
    int getFps()
    {
        return 1 / deltaTime;
    }
    void setOnStartCallback(std::function<void()> callback)
    {
        onStart = callback;
    }
    void setOnUpdateCallback(std::function<void()> callback)
    {
        onUpdate = callback;
    }
    int width;
    int height;
    bool fullscreen = false;
    GLFWwindow *window;
    void framebuffer_size_callback(GLFWwindow *window, int width, int height);
    void toggleFullscreen();

private:
    int baseHeight = 100;
    int baseWidth = 100;
    int baseX = 0;
    int baseY = 0;
    int maxFps = 60;
    double deltaTime = 0.0f;
    const char *title_;
    bool running = false;
    std::function<void()> onStart;
    std::function<void()> onUpdate;
    GLFWmonitor *monitor = nullptr;
    const GLFWvidmode *mode = nullptr;
    void processInput();
};
void setWindowPointer(Window *window);
Window *getWindowPointer();
#endif