#include <window.h>
#include <iostream>
#include <filesystem>
#include <vector>
#include <unordered_map>
#include <string>
#include <stdexcept>
#include <memory>

namespace fs = std::filesystem;

Window::Window(int height, int width, const char *title)
    : logger("\e[95mENGINE")
{
    this->height = height;
    this->width = width;
    this->title = title;
}

Window::Window(int height, int width, const char *title, bool debug)
    : logger("\e[95mENGINE", debug)
{
    this->height = height;
    this->width = width;
    this->title = title;
    this->debug = debug;
}

GameObject* Window::getObjectById(const std::string& id)
{
    auto it = std::find_if(objects.begin(), objects.end(), [&](const GameObject &obj) { return obj.id == id; });
    return (it != objects.end()) ? &(*it) : nullptr;
}

GameObject* Window::getObjectByName(const std::string& name)
{
    auto it = std::find_if(objects.begin(), objects.end(), [&](const GameObject &obj) { return obj.name == name; });
    return (it != objects.end()) ? &(*it) : nullptr;
}
void getAllFiles(const fs::path &directory, std::vector<fs::path> &files)
{
        // Iterate through the directory and its subdirectories
        for (const auto &entry : fs::recursive_directory_iterator(directory))
        {
                if (fs::is_regular_file(entry))
                {
                        files.push_back(entry.path());
                }
        }
}
void Window::init()
{
    if (!glfwInit())
    {
        logger.log(LogLevel::ERROR, "Failed to initialize GLFW");
        throw std::runtime_error("Failed to initialize GLFW");
    }
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    const GLFWvidmode *mode = glfwGetVideoMode(glfwGetPrimaryMonitor());
    window = glfwCreateWindow(width, height, title, NULL, NULL);
    if (window == NULL)
    {
        logger.log(LogLevel::ERROR, "Failed to create GLFW window");
        throw std::runtime_error("Failed to create GLFW window");
    }
    glfwMakeContextCurrent(window);
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        logger.log(LogLevel::ERROR, "Failed to initialize GLAD");
        throw std::runtime_error("Failed to initialize GLAD");
    }
    logger.log(LogLevel::INFO, "Loading shaders");
    std::vector<fs::path> files;
    getAllFiles("engine/shaders", files);
    for (const auto &file : files)
    {
        if (file.extension() == ".vs")
        {
            logger.log(LogLevel::INFO, "Loading shader: " + file.stem().string());
            Shader current = Shader(file.string().c_str(), (file.parent_path().string() + std::string("/") + file.stem().string() + ".fs").c_str());
            shaderRegistry[file.stem().string()] = current;
        }
    }
}

bool Window::shaderExists(const std::string &shaderName)
{
    return shaderRegistry.find(shaderName) != shaderRegistry.end();
}

Shader* Window::getShader(const std::string& shaderName)
{
    auto it = shaderRegistry.find(shaderName);
    return (it != shaderRegistry.end()) ? &it->second : nullptr;
}

void Window::start()
{
    while (!glfwWindowShouldClose(window))
    {
        inputCallback(this);
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        for (auto &obj : objects)
        {
            obj.render();
        }

        updateCallback(this);
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    logger.log(LogLevel::INFO, "Terminating window");
    logger.log(LogLevel::INFO, "Cleaning up");
    for (auto &obj : objects)
    {
        logger.log(LogLevel::DEBUG, "Freeing resources for object with ID: " + obj.id);
        obj.freeResources();
    }
    glfwTerminate();
    logger.log(LogLevel::INFO, "Window terminated");
    return;
}

void Window::setUpdateCallback(std::function<void(Window*)> callback)
{
    if (callback == nullptr)
    {
        throw std::invalid_argument("Update function cannot be null");
    }
    updateCallback = callback;
}

void Window::setInputCallback(std::function<void(Window*)> callback)
{
    if (callback == nullptr)
    {
        throw std::invalid_argument("Input processor function cannot be null");
    }
    inputCallback = callback;
}

void Window::registerObject(GameObject obj)
{
    logger.log(LogLevel::DEBUG, "Registering object with ID: " + obj.id);
    if (obj.shader == nullptr)
    {
        obj.useShader(getShader(obj.shaderName));
    }
    obj.build();
    objects.push_back(std::move(obj));
}

