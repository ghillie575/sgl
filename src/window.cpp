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

void Window::framebuffer_size_callback(GLFWwindow *window, int width, int height)
{
    glViewport(0, 0, width, height);
}

GameObject *Window::getObjectById(std::string id)
{
    for ( auto &obj : objects)
    {
        if (obj.id == id)
        {
            return &obj;
        }
    }
    return nullptr;
}

GameObject *Window::getObject(std::string name)
{
    for ( auto &obj : objects)
    {
        if (obj.name == name)
        {
            return &obj;
        }
    }
    return nullptr;
}
void getAllFiles(const fs::path &directory, std::vector<fs::path> &files, int &fileCOunt)
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
void Window::Init()
{
    if (!glfwInit())
    {
        logger.log(LogLevel::ERROR, "Failed to initialize GLFW");
        std::cerr << "GLFW init failed" << std::endl;
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
        std::cerr << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        throw std::runtime_error("Failed to create GLFW window");
    }
    glfwMakeContextCurrent(window);
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        logger.log(LogLevel::ERROR, "Failed to initialize GLAD");
        std::cerr << "Failed to initialize GLAD" << std::endl;
        throw std::runtime_error("Failed to initialize GLAD");
    }
    logger.log(LogLevel::INFO, "Loading shaders");
    std::vector<fs::path> files;
    int count;
    getAllFiles("engine/shaders", files, count);

    for (const auto &file : files)
    {
        if (file.extension() == ".vs")
        {
            logger.log(LogLevel::INFO, "Loading shader: " + file.stem().string());
            Shader current = Shader(file.string().c_str(), (file.parent_path().string() + std::string("/") + file.stem().string() + ".fs").c_str());
            shadreReg[file.stem().string()] = current;
        }
    }
}

bool Window::shaderExists(const std::string &shaderName)
{
    return shadreReg.find(shaderName) != shadreReg.end();
}

Shader *Window::getShader(std::string shaderName)
{
    if (shaderExists(shaderName))
    {
        return &shadreReg[shaderName];
    }
    else
    {
        return &shadreReg["default"];
    }
}

void Window::start()
{
    while (!glfwWindowShouldClose(window))
    {
        Input(this);
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        for ( auto &obj : objects)
        {
            obj.render();
        }

        update(this);
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    logger.log(LogLevel::INFO, "Terminating window");
    logger.log(LogLevel::INFO, "Cleaning up");
    for ( auto &obj : objects)
    {
        logger.log(LogLevel::DEBUG, "Freeing resources for object with ID: " + obj.id);
        obj.freeResources();
    }
    glfwTerminate();
    logger.log(LogLevel::INFO, "Window terminated");
    return;
}

void Window::setUpdate(void (*func)(Window *window))
{
    if (func == nullptr)
    {
        throw std::invalid_argument("Update function cannot be null");
    }
    update = func;
}

void Window::setInputProcess(void (*func)(Window *window))
{
    if (func == nullptr)
    {
        throw std::invalid_argument("Input processor function cannot be null");
    }
    Input = func;
}

void Window::regObject(GameObject obj)
{
    logger.log(LogLevel::DEBUG, "Registering object with ID: " + obj.id);
    if (obj.shader == nullptr)
    {
        obj.useShader(getShader(obj.shaderName));
    }
    obj.build();
    objects.insert(objects.begin(), obj);
}

