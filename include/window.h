#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <object.h>
#include <vector>
#include <unordered_map>
#include <string>
#include <functional>
#include <logger.h>

class Window
{
private:
    int height;
    int width;
    const char *title;
    bool debug = false;
    GLFWwindow *window;
    std::unordered_map<std::string, Shader> shaderRegistry;
    std::vector<GameObject> objects;
    Logger logger;
    std::function<void(Window*)> updateCallback;
    std::function<void(Window*)> inputCallback;

    static void framebufferSizeCallback(GLFWwindow *window, int width, int height)
    {
        Window *win = static_cast<Window*>(glfwGetWindowUserPointer(window));
        win->width = width;
        win->height = height;
        glViewport(0, 0, width, height);
    }

public:
    Window(int height, int width, const char *title);
    Window(int height, int width, const char *title, bool debug);
    void init();
    void setUpdateCallback(std::function<void(Window*)> callback);
    void setInputCallback(std::function<void(Window*)> callback);
    void registerObject(GameObject obj);
    GameObject* getObjectById(const std::string& id);
    GameObject* getObjectByName(const std::string& name);
    Shader* getShader(const std::string& shaderName);
    bool shaderExists(const std::string &shaderName);
    void start();
};

