#include <sgl/window.h>
#include <sgl/render.h>
#include <GLFW/glfw3.h>
#include <stdexcept>
bool s_showStats = false;
void SGLWindow::glfw_errorCallback(int error, const char *description)
{
    Logger("Window").log("GLFW error " + std::to_string(error) + ": " + description, Logger::Level::ERROR);
}

void SGLWindow::glfw_keyCallback(GLFWwindow *window, int key, int scancode, int action, int mods)
{
    if (key == GLFW_KEY_F12 && action == GLFW_RELEASE)
        s_showStats = !s_showStats;
}
void SGLWindow::init()
{
    if (!glfwInit())
    {
        logger.log("Failed to initialize GLFW", Logger::Level::ERROR);
        throw std::runtime_error("Failed to initialize GLFW");
    }

    glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
    window = glfwCreateWindow(width, height, title.c_str(), nullptr, nullptr);
    if (!window)
    {
        glfwTerminate();
        logger.log("Failed to create GLFW window", Logger::Level::ERROR);
        throw std::runtime_error("Failed to create GLFW window");
    }
    glfwSetErrorCallback(glfw_errorCallback);
    glfwSetKeyCallback(window, glfw_keyCallback);
    initBGFX(window);
    if (debuggerEnabled)
    {
        initDebugger();
    }
}
void SGLWindow::start()
{
    while (!glfwWindowShouldClose(window))
    {
        glfwPollEvents();
        bgfx::touch(0);
        // handle window resize
        int oldWidth = width, oldHeight = height;
        glfwGetWindowSize(window, &width, &height);
        if (width != oldWidth || height != oldHeight)
        {
            bgfx::reset((uint32_t)width, (uint32_t)height, BGFX_RESET_VSYNC);
            bgfx::setViewRect(0, 0, 0, bgfx::BackbufferRatio::Equal);
        }
        bgfx::dbgTextClear();
        bgfx::dbgTextPrintf(0, 1, 0x0f, "SGL v0.1");
        bgfx::dbgTextPrintf(0, 2, 0x0f, "Press F12 to toggle stats");
        bgfx::setDebug(s_showStats ? BGFX_DEBUG_STATS : BGFX_DEBUG_TEXT);

        bgfx::frame();
    }
    shutdownBGFX();
    glfwDestroyWindow(window);
    glfwTerminate();
}