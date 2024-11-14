#include <window.h>
#include <iostream>

Window::Window(int height, int width, const char *title)
{
        this->height = height;
        this->width = width;
        this->title = title;
}

void Window::framebuffer_size_callback(GLFWwindow *window, int width, int height)
{
        glViewport(0, 0, width, height);
}
Object &Window::getObject(int id)
{
        return objects[id];
}
void Window::Init()
{
        glfwInit();
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
        const GLFWvidmode *mode = glfwGetVideoMode(glfwGetPrimaryMonitor());
        window = glfwCreateWindow(width, height, title, NULL, NULL);
        if (window == NULL)
        {
                std::cout << "Engine init failed:\nFailed to create GLFW window\nat Window::Init()" << std::endl;
                glfwTerminate();
                exit(-1);
        }
        glfwMakeContextCurrent(window);
        if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
        {
                std::cout << "Engine init failed:\nFailed to initialize GLAD\nat Window::Init()" << std::endl;
                exit(-1);
        }
}
void Window::start()
{
        while (!glfwWindowShouldClose(window))
        {
                // processInput(window);
                Input(this);
                glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
                glClear(GL_COLOR_BUFFER_BIT);
                for (int i = 0; i < objects.size(); i++)
                {
                        objects[i].render();
                }

                update(this);
                glfwSwapBuffers(window);
                glfwPollEvents();
        }
        for (int i = 0; i < objects.size(); i++)
        {
                objects[i].freeResources();
        }
        glfwTerminate();
        
        return;
}
void Window::setUpdate(void (*func)(Window *window))
{
        update = func;
}
void Window::setInputProcess(void (*func)(Window *window))
{
        Input = func;
}
void Window::regObject(Object obj)
{

        obj.build();
        objects.insert(objects.begin(), obj);
}
