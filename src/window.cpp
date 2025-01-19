/**
 * @file window.cpp
 * @brief Contains the implementation of the Window class
 * @author Petr Fučík
 */

#include <SGL/window.h>
#include <iostream>
#include <filesystem>
#include <vector>
#include <unordered_map>
#include <string>
#include <stdexcept>
#include <memory>
namespace fs = std::filesystem;

/**
 * Constructor for the Window class
 * @param height The height of the window in pixels
 * @param width The width of the window in pixels
 * @param title The title of the window
 */
Window::Window(int height, int width, const char *title)
    : logger("\e[95mENGINE")
{
    this->height = height;
    this->width = width;
    this->title = title;
    std::cout << "Hello, from XandO!\n";

    
}

/**
 * Constructor for the Window class with debug flag
 * @param height The height of the window in pixels
 * @param width The width of the window in pixels
 * @param title The title of the window
 * @param debug If true, the window will be created with debug logging enabled
 */
Window::Window(int height, int width, const char *title, bool debug)
    : logger("\e[95mENGINE", debug)
{
    this->height = height;
    this->width = width;
    this->title = title;
    this->debug = debug;
    std::cout << "Hello, from XandO!\n";
  
}
void Window::camUpdate(){
        camera.setProjectionMatrix(glm::perspective(glm::radians(45.0f), (float)width / (float)height, 0.1f, 100.0f));
        for (auto &obj : this->shaderRegistry)
        {
            obj.second.setMat4("projection", this->camera.getProjectionMatrix());
        }
}
void Window::camInit()
{
    camera.setPosition(glm::vec3(0.0f, 0.0f, -2.0f));
    camera.setRotation(glm::vec3(0.0f, 0.0f, 0.0f));
    camera.setProjectionMatrix(glm::perspective(glm::radians(45.0f), (float)width / (float)height, 0.1f, 100.0f));
}
/**
 * Returns a pointer to the GameObject with the given ID
 * @param id The ID of the GameObject to retrieve
 * @return A pointer to the GameObject with the given ID, or nullptr if no such object exists
 */
GameObject* Window::getObjectById(const std::string& id)
{
 auto it = std::find_if(objects.begin(), objects.end(), [&](const std::shared_ptr<GameObject>& obj) {
    return obj->id == id;  // Access id through the shared_ptr
});
return (it != objects.end()) ? it->get() : nullptr;  // Use it->get() to return the raw pointer

}

/**
 * Returns a pointer to the GameObject with the given name
 * @param name The name of the GameObject to retrieve
 * @return A pointer to the GameObject with the given name, or nullptr if no such object exists
 */
GameObject* Window::getObjectByName(const std::string& name)
{
    auto it = std::find_if(objects.begin(), objects.end(), [&](const std::shared_ptr<GameObject>& obj) {
    return obj->name == name;  // Use obj->name to access the name member
});
return (it != objects.end()) ? it->get() : nullptr;  // Use it->get() to return a raw pointer

}

/**
 * Retrieves all files in the given directory and its subdirectories
 * @param directory The directory to search in
 * @param files A vector to store the found files
 */
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
    void Window::framebufferSizeCallback(GLFWwindow *window, int width, int height)
    {
        Window *self = static_cast<Window*>(glfwGetWindowUserPointer(window));
        self->height = height;
        self->width = width;
        self->camUpdate();
        glViewport(0, 0, width, height);
    }
/**
 * Initializes the window
 */
void Window::init()
{
    closed = false;
    if (!glfwInit())
    {
        logger.log(LogLevel::ERROR, "Failed to initialize GLFW");
        throw std::runtime_error("Failed to initialize GLFW");
    }
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    if (dobbleBuffering)
    {
        glfwWindowHint(GLFW_DOUBLEBUFFER, GLFW_TRUE);
    }
    else
    {
        glfwWindowHint(GLFW_DOUBLEBUFFER, GLFW_FALSE);
    }
    const GLFWvidmode *mode = glfwGetVideoMode(glfwGetPrimaryMonitor());
    window = glfwCreateWindow(width, height, title.c_str(), NULL, NULL);
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
    glfwSetWindowUserPointer(window, this);
    camInit();
    glEnable(GL_DEPTH_TEST);
    logger.log(LogLevel::INFO, "Loading libraries");
    LibraryLoader loader("engine/libraries");
    loader.loadLibraries(this);
    logger.log(LogLevel::INFO, "Libraries loaded");
    logger.log(LogLevel::INFO, "Loading shaders");
    std::vector<fs::path> files;
    getAllFiles("engine/shaders", files);
    for (const auto &file : files)
    {
        if (file.extension() == ".vs")
        {
            logger.log(LogLevel::INFO, "Loading shader: " + file.stem().string());
            Shader current = Shader(file.string().c_str(), (file.parent_path().string() + std::string("/") + file.stem().string() + ".fs").c_str());
            current.setMat4("view", camera.getViewMatrix());
            current.setMat4("projection", camera.getProjectionMatrix());
            shaderRegistry[file.stem().string()] = current;
        }
    }
    logger.log(LogLevel::INFO, "Shaders loaded");
    logger.log(LogLevel::INFO,"Loading types");
    loader.executeOnTypeRegister(this);
    onTypeRegister(this);
    factory.registerObject("default", []() { return std::make_shared<GameObject>(); });
    logger.log(LogLevel::INFO, "Types loaded");
    glfwSetFramebufferSizeCallback(window, framebufferSizeCallback);
    logger.log(LogLevel::INFO, "Window initialized");
}

/**
 * Checks if a shader with the given name exists
 * @param shaderName The name of the shader to check
 * @return True if the shader exists, false otherwise
 */
bool Window::shaderExists(const std::string &shaderName)
{
    return shaderRegistry.find(shaderName) != shaderRegistry.end();
}

/**
 * Returns a pointer to the shader with the given name
 * @param shaderName The name of the shader to retrieve
 * @return A pointer to the shader with the given name, or nullptr if no such shader exists
 */
Shader* Window::getShader(const std::string& shaderName)
{
    auto it = shaderRegistry.find(shaderName);
    return (it != shaderRegistry.end()) ? &it->second : nullptr;
}

/**
 * Starts the window's main loop
 */
void Window::start()
{
    
    for (const auto &obj : objects)
    {
        obj->start();
    }
    
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    while (!glfwWindowShouldClose(window))
    {
        inputCallback(this);
        CalculateFrameRate();
        
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        for (auto &obj : objects)
        {
            obj->render();
        }

        updateCallback(this);
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    logger.log(LogLevel::INFO, "Terminating window");
    logger.log(LogLevel::INFO, "Cleaning up");
    for (auto &obj : objects)
    {
        logger.log(LogLevel::DEBUG, "Freeing resources for object with ID: " + obj->id);
        obj->freeResources();
    }
    factory.freeResources();
    glfwTerminate();
    closed = true;
    logger.log(LogLevel::INFO, "Window terminated");
    
    return;
}

/**
 * Sets the update callback function
 * @param callback The function to call on each frame
 */
void Window::setUpdateCallback(std::function<void(Window*)> callback)
{
    if (callback == nullptr)
    {
        throw std::invalid_argument("Update function cannot be null");
    }
    updateCallback = callback;
}

/**
 * Sets the input processing callback function
 * @param callback The function to call on each frame for input processing
 */
void Window::setInputCallback(std::function<void(Window*)> callback)
{
    if (callback == nullptr)
    {
        throw std::invalid_argument("Input processor function cannot be null");
    }
    inputCallback = callback;
}

/**
 * Registers a GameObject with the window
 * @param obj The GameObject to register
 */
void Window::registerObject(std::shared_ptr<GameObject> obj)
{
    logger.log(LogLevel::DEBUG, "Registering object with ID: " + obj->id);
    if (obj->shader == nullptr)
    {
        obj->useShader(getShader(obj->shaderName));
    }
    obj->build();  // Now calls the correct build() method
    objects.push_back(std::move(obj));
}

/**
 * Calculates the current frame rate
 */
void Window::CalculateFrameRate()
{
    static double previousTime = glfwGetTime();
    double currentTime = glfwGetTime();
    double deltaTime = currentTime - previousTime;
    previousTime = currentTime;
    time.setDeltaTime(deltaTime);
    fps = (int)(1.0 / deltaTime);
}

/**
 * Returns the current frame rate
 * @return The current frame rate
 */
int Window::getCurrentFps()
{
    logger.log(LogLevel::DEBUG, "Current FPS: " + std::to_string(fps));
    return fps;
}

/**
 * Checks if the window is closed
 * @return True if the window is closed, false otherwise
 */
bool Window::IsClosed()
{
    return closed;
}

/**
 * Sets whether the window should use double buffering
 * @param value True if the window should use double buffering, false otherwise
 */
void Window::setDobbleBuffering(bool value)
{
    dobbleBuffering = value;
    
}
void Window::setOnTypeRegister(std::function<void(Window*)> callback)
{
    if (callback == nullptr)
    {
        logger.log(LogLevel::ERROR, "OnTypeRegister function cannot be null");
        throw std::invalid_argument("OnTypeRegister function cannot be null");
    }
    onTypeRegister = callback;
}

