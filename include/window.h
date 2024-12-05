#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <object.h>
#include <iostream>
#include <vector>
#include <logger.h>
#ifndef WINDOW_H
#define WINDOW_H
class Window
{
private:
    int height;
    int width;
    const char *title;
    //std::vector<Object> Objects;
    std::unordered_map<std::string, Shader> shadreReg;
    std::vector<Object> objects;
    Logger logger = Logger("ENGINE");
    void (*update)(Window *window);
    void (*Input)(Window *window);
    void framebuffer_size_callback(GLFWwindow *window, int width, int height);
    bool shaderExists(const std::string& shaderName);
    

public:
    GLFWwindow *window;
    Window(int height, int width, const char *title);
    void Init();
    void setUpdate(void (*func)(Window *window));
    void setInputProcess(void (*func)(Window *window));
    void regObject(Object obj);
    Object* getObject(int id);
    Shader* getShader(std::string shaderName);
    void start();
};
#endif
