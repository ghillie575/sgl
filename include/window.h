#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <object.h>
#include <iostream>
#include <vector>
#ifndef WINDOW_H
#define WINDOW_H
class Window
{
private:
    int height;
    int width;
    const char *title;
    //std::vector<Object> Objects;
    std::vector<Object> objects;
    void (*update)(Window *window);
    void (*Input)(Window *window);
    void framebuffer_size_callback(GLFWwindow *window, int width, int height);
    

public:
    GLFWwindow *window;
    Window(int height, int width, const char *title);
    void Init();
    void setUpdate(void (*func)(Window *window));
    void setInputProcess(void (*func)(Window *window));
    void regObject(Object obj);
    Object& getObject(int id);
    void start();
};
#endif
