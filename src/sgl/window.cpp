#include <sgl/window.h>
#include <sgl/logger.h>
#include <sgl/engine/gl_engine.h>
#include <iostream>
void framebuffer_size_callback(GLFWwindow *window, int width, int height)
{
    glViewport(0, 0, width, height);
}
Window::Window(int w, int h, const char* title) : width_(w), height_(h), title_(title), window(nullptr) {}
int Window::init()
{
    getEngine()->initialize();
    window = glfwCreateWindow(width_,height_,title_, NULL, NULL);
    if (window == NULL)
    {
        getLogger()->error("Window", "Failed to create GLFW window");
        glfwTerminate();
        return 1;
    }
    glfwMakeContextCurrent(window);
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        getLogger()->error("Window", "Failed to initialize GLAD");
        return 2;
    }
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    return 0;
}
void Window::start()
{
    while (!glfwWindowShouldClose(window))
    {
        glfwSwapBuffers(window);
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        glfwPollEvents();
    }
}
void Window::cleanup()
{
    glfwTerminate();
}
