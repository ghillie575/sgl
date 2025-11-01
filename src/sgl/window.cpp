#include <sgl/window.h>
#include <sgl/logger.h>
#include <sgl/core/gl_engine.h>
#include <sgl/loaders/shader_loader.h>
#include <iostream>
#include <chrono>
#include <thread>
Window *_window; // global instance
void setWindowPointer(Window *window)
{
    _window = window;
}
Window *getWindowPointer()
{
    return _window;
}
void framebuffer_size_callback_glfw(GLFWwindow *window, int width, int height)
{
    getWindowPointer()->framebuffer_size_callback(window, width, height);
}
void Window::framebuffer_size_callback(GLFWwindow *window, int width, int height)
{
    glViewport(0, 0, width, height);
    this->width = width;
    this->height = height;
    Shader *shader = getShaderByName("debug_text");
    if (!shader)
    {
        return;
    }
    glm::mat4 projection = glm::ortho(0.0f, static_cast<float>(width), 0.0f, static_cast<float>(height));
    shader->use();
    shader->setMat4("projection", projection);
}
Window::Window(int w, int h, const char *title) : width(w), height(h), title_(title), window(nullptr) {}
int Window::init()
{
    window = glfwCreateWindow(width, height, title_, NULL, NULL);
    if (window == NULL)
    {
        getLogger()->error("Window", "Failed to create GLFW window");
        glfwTerminate();
        return 1;
    }
    glfwMakeContextCurrent(window);
    glfwSwapInterval(0); // Disable VSync
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        getLogger()->error("Window", "Failed to initialize GLAD");
        return 2;
    }
    getEngine()->version = glGetString(GL_VERSION);
    getEngine()->renderer = glGetString(GL_RENDERER);
    getEngine()->vendor = glGetString(GL_VENDOR);
    getEngine()->shaderV = glGetString(GL_SHADING_LANGUAGE_VERSION);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback_glfw);
    return 0;
}
void Window::processInput()
{
    static bool wasPressed = false;

    int state = glfwGetKey(window, GLFW_KEY_F11);

    if (state == GLFW_PRESS && !wasPressed)
    {
        toggleFullscreen();
        wasPressed = true;
    }
    else if (state == GLFW_RELEASE && wasPressed)
    {
        wasPressed = false;
    }
}

void Window::toggleFullscreen()
{
    fullscreen = !fullscreen;

    if (fullscreen)
    {
        // Save current window info
        glfwGetWindowPos(window, &baseX, &baseY);
        glfwGetWindowSize(window, &baseWidth, &baseHeight);

        // Find which monitor the window is currently on
        int windowCenterX = baseX + baseWidth / 2;
        int windowCenterY = baseY + baseHeight / 2;
        int monitorCount;
        GLFWmonitor **monitors = glfwGetMonitors(&monitorCount);
        monitor = monitors[0];

        for (int i = 0; i < monitorCount; i++)
        {
            int mx, my;
            glfwGetMonitorPos(monitors[i], &mx, &my);
            const GLFWvidmode *m = glfwGetVideoMode(monitors[i]);

            if (windowCenterX >= mx && windowCenterX <= mx + m->width &&
                windowCenterY >= my && windowCenterY <= my + m->height)
            {
                monitor = monitors[i];
                break;
            }
        }

        mode = glfwGetVideoMode(monitor);

        glfwSetWindowMonitor(window, monitor, 0, 0, mode->width, mode->height, mode->refreshRate);
    }
    else
    {
        // Restore window to its previous size and position on the same monitor
        glfwSetWindowMonitor(window, nullptr, baseX, baseY, baseWidth, baseHeight, 0);
    }
}

void Window::start()
{
    this->running = true;
    this->onStart();
    getLogger()->log("Window", "Starting main loop");
    double lastFrame = glfwGetTime();

    while (!glfwWindowShouldClose(window))
    {
        double currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;
        processInput();
        // Clear color
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        // Update
        if (onUpdate)
            onUpdate();

        // Swap buffers & poll events
        glfwSwapBuffers(window);
        glfwPollEvents();

        // --- FPS limiting ---
        double frameEnd = glfwGetTime();
        double frameTime = frameEnd - currentFrame;
        double target = 1.0 / maxFps;

        if (frameTime < target)
            std::this_thread::sleep_for(std::chrono::duration<double>(target - frameTime));
    }

    running = false;
}
void Window::cleanup()
{
    glfwTerminate();
}
bool Window::isRunning()
{
    return running;
}
void Window::setFpsLimit(int fps)
{
    maxFps = fps;
}
