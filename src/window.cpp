// Copyright (c) 2025 Mikhail Karakou
#include <stdexcept>
#include <iostream>
#include <vector>
#include <string>
#include <memory>
#include <algorithm>
#include <functional>
#include <filesystem>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <SGL/logger.h>
#include <SGL/shader.h>
#include <SGL/object.h>
#include <SGL/libraryloader.h>
#include <SGL/window.h>
#include <SGL/UI/ui-element.h>

namespace SGL
{

    // Constructor for Window class
    Window::Window(int height, int width, const char *title)
        : logger("\e[95mENGINE")
    {
        try
        {
            this->height = height;
            this->width = width;
            this->title = title;
            std::cout << "Hello, from XandO!\n";
        }
        catch (const std::exception &e)
        {
            logger.log(LogLevel::ERROR, "Exception in Window constructor: " + std::string(e.what()));
            throw;
        }
    }

    // Constructor for Window class with debug option
    Window::Window(int height, int width, const char *title, bool debug)
        : logger("\e[95mENGINE", debug)
    {
        try
        {
            this->height = height;
            this->width = width;
            this->title = title;
            this->debug = debug;
            std::cout << "Hello, from XandO!\n";
        }
        catch (const std::exception &e)
        {
            logger.log(LogLevel::ERROR, "Exception in Window constructor with debug: " + std::string(e.what()));
            throw;
        }
    }

    // Update camera projection matrix
    void Window::camUpdate()
    {
        try
        {
            camera.setProjectionMatrix(glm::perspective(glm::radians(FOV), (float)width / (float)height, 0.1f, 100.0f));
            for (auto &obj : this->shaderRegistry)
            {
                obj.second.setMat4("projection", this->camera.getProjectionMatrix());
            }
        }
        catch (const std::exception &e)
        {
            logger.log(LogLevel::ERROR, "Exception in camUpdate: " + std::string(e.what()));
            throw;
        }
    }

    // Initialize camera settings
    void Window::camInit()
    {
        try
        {
            camera.setPosition(glm::vec3(0.0f, 0.0f, -2.0f));
            camera.setRotation(glm::vec3(0.0f, 0.0f, 0.0f));
            camera.setProjectionMatrix(glm::perspective(glm::radians(45.0f), (float)width / (float)height, 0.1f, 100.0f));
        }
        catch (const std::exception &e)
        {
            logger.log(LogLevel::ERROR, "Exception in camInit: " + std::string(e.what()));
            throw;
        }
    }

    // Get object by ID
    GameObject *Window::getObjectById(const std::string &id)
    {
        try
        {
            auto it = std::find_if(objects.begin(), objects.end(), [&](const std::shared_ptr<GameObject> &obj)
                                   { return obj->id == id; });
            return (it != objects.end()) ? it->get() : nullptr;
        }
        catch (const std::exception &e)
        {
            logger.log(LogLevel::ERROR, "Exception in getObjectById: " + std::string(e.what()));
            throw;
        }
    }
    UI::UIElement *Window::getUiElementById(const std::string &id)
    {
        try
        {
            auto it = std::find_if(uiElements.begin(), uiElements.end(), [&](const std::shared_ptr<UI::UIElement> &obj)
                                   { return obj->id == id; });
            return (it != uiElements.end()) ? it->get() : nullptr;
        }
        catch (const std::exception &e)
        {
            logger.log(LogLevel::ERROR, "Exception in getObjectById: " + std::string(e.what()));
            throw;
        }
    }
    // Get object by name
    GameObject *Window::getObjectByName(const std::string &name)
    {
        try
        {
            auto it = std::find_if(objects.begin(), objects.end(), [&](const std::shared_ptr<GameObject> &obj)
                                   { return obj->name == name; });
            return (it != objects.end()) ? it->get() : nullptr;
        }
        catch (const std::exception &e)
        {
            logger.log(LogLevel::ERROR, "Exception in getObjectByName: " + std::string(e.what()));
            throw;
        }
    }

    // Get all files in a directory
    void getAllFiles(const fs::path &directory, std::vector<fs::path> &files)
    {
        try
        {
            for (const auto &entry : fs::recursive_directory_iterator(directory))
            {
                if (fs::is_regular_file(entry))
                {
                    files.push_back(entry.path());
                }
            }
        }
        catch (const std::exception &e)
        {
            std::cerr << "Exception in getAllFiles: " << e.what() << std::endl;
            throw;
        }
    }

    // Callback for framebuffer size changes
    void Window::framebufferSizeCallback(GLFWwindow *window, int width, int height)
    {
        try
        {
            Window *self = static_cast<Window *>(glfwGetWindowUserPointer(window));
            self->height = height;
            self->width = width;
            self->camUpdate();
            glViewport(0, 0, width, height);
        }
        catch (const std::exception &e)
        {
            Window *self = static_cast<Window *>(glfwGetWindowUserPointer(window));
            self->logger.log(LogLevel::ERROR, "Exception in framebufferSizeCallback: " + std::string(e.what()));
            throw;
        }
    }

    // Pre-initialize window settings
    void Window::preInit()
    {
        try
        {
            if (!glfwInit())
            {
                logger.log(LogLevel::ERROR, "Failed to initialize GLFW");
                throw std::runtime_error("Failed to initialize GLFW");
            }
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
            glfwHideWindow(window);
            if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
            {
                logger.log(LogLevel::ERROR, "Failed to initialize GLAD");
                throw std::runtime_error("Failed to initialize GLAD");
            }
            glfwSetWindowUserPointer(window, this);
        }
        catch (const std::exception &e)
        {
            logger.log(LogLevel::ERROR, "Exception in preInit: " + std::string(e.what()));
            throw;
        }
    }
    void Window::unlockCursor()
    {
        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
    }
    // Pre-initialize window settings with OpenGL version
    void Window::preInit(int glVersionMajor, int glVersionMinor)
    {
        try
        {
            if (!glfwInit())
            {
                logger.log(LogLevel::ERROR, "Failed to initialize GLFW");
                throw std::runtime_error("Failed to initialize GLFW");
            }
            logger.log(LogLevel::WARN, "Initializing GLFW with OpenGL version " + std::to_string(glVersionMajor) + "." + std::to_string(glVersionMinor));
            glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, glVersionMajor);
            glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, glVersionMinor);
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
            glfwHideWindow(window);
            glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
            if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
            {
                logger.log(LogLevel::ERROR, "Failed to initialize GLAD");
                throw std::runtime_error("Failed to initialize GLAD");
            }
            glfwSetWindowUserPointer(window, this);
        }
        catch (const std::exception &e)
        {
            logger.log(LogLevel::ERROR, "Exception in preInit with version: " + std::string(e.what()));
            throw;
        }
    }

    // Initialize window and load resources
    void Window::init()
    {
        try
        {
            closed = false;
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
                    current.setVec3("lightColor", lightEnv.sunColor);
                    current.setVec3("lightPos", lightEnv.sunPos);
                    current.setFloat("ambientStrength", lightEnv.ambientStrenght);
                    current.setMat4("projection", camera.getProjectionMatrix());
                    shaderRegistry[file.stem().string()] = current;
                }
            }
            logger.log(LogLevel::INFO, "Shaders loaded");
            logger.log(LogLevel::INFO, "Loading types");
            loader.executeOnTypeRegister(this);
            onTypeRegister(this);
            factory.registerObject("default", []()
                                   { return std::make_shared<GameObject>(); });
            logger.log(LogLevel::INFO, "Types loaded");
            glfwSetFramebufferSizeCallback(window, framebufferSizeCallback);
            glfwSetCursorPosCallback(window, mouse_callback);
            logger.log(LogLevel::INFO, "Window initialized");
            glfwShowWindow(window);
        }
        catch (const std::exception &e)
        {
            logger.log(LogLevel::ERROR, "Exception in init: " + std::string(e.what()));
            throw;
        }
    }

    // Check if shader exists
    bool Window::shaderExists(const std::string &shaderName)
    {
        try
        {
            return shaderRegistry.find(shaderName) != shaderRegistry.end();
        }
        catch (const std::exception &e)
        {
            logger.log(LogLevel::ERROR, "Exception in shaderExists: " + std::string(e.what()));
            throw;
        }
    }

    // Get shader by name
    Shader *Window::getShader(const std::string &shaderName)
    {
        try
        {
            auto it = shaderRegistry.find(shaderName);
            return (it != shaderRegistry.end()) ? &it->second : nullptr;
        }
        catch (const std::exception &e)
        {
            logger.log(LogLevel::ERROR, "Exception in getShader: " + std::string(e.what()));
            throw;
        }
    }

    // Start the window rendering loop
    void Window::start()
    {
        try
        {
            for (const auto &obj : objects)
            {
                obj->start();
            }
            glClearColor(0.1529f, 0.1608f, 0.1686f, 1.0f);
            while (!glfwWindowShouldClose(window))
            {
                inputCallback(this);
                CalculateFrameRate();
                glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
                for (auto &element : uiElements)
                {
                    if (element->visible)
                    {
                        element->draw();
                    }
                }
                glUseProgram(0);
                for (auto &obj : objects)
                {
                    obj->render(this);
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
        }
        catch (const std::exception &e)
        {
            logger.log(LogLevel::ERROR, "Exception in start: " + std::string(e.what()));
            throw;
        }
    }

    // Set update callback function
    void Window::setUpdateCallback(std::function<void(Window *)> callback)
    {
        if (callback == nullptr)
        {
            logger.log(LogLevel::ERROR, "Update function cannot be null");
            throw std::invalid_argument("Update function cannot be null");
        }
        updateCallback = callback;
    }

    // Set input callback function
    void Window::setInputCallback(std::function<void(Window *)> callback)
    {
        if (callback == nullptr)
        {
            logger.log(LogLevel::ERROR, "Input processor function cannot be null");
            throw std::invalid_argument("Input processor function cannot be null");
        }
        inputCallback = callback;
    }
    void Window::setMouseCallback(std::function<void(Window *, double, double)> callback)
    {
        if (callback == nullptr)
        {
            logger.log(LogLevel::ERROR, "Mouse processor function cannot be null");
            throw std::invalid_argument("Mouse processor function cannot be null");
        }
        mouseCallback = callback;
    }

    // Register a game object
    void Window::registerObject(std::shared_ptr<GameObject> obj)
    {
        try
        {
            logger.log(LogLevel::DEBUG, "Registering object with ID: " + obj->id);
            if (!obj->shaderName.empty())
            {
                obj->useShader(getShader(obj->shaderName));
            }
            else if (obj->shader == nullptr)
            {
                obj->useShader(getShader("default"));
            }
            else
            {
                obj->useShader(getShader("default"));
            }
            obj->build();
            objects.push_back(std::move(obj));
        }
        catch (const std::exception &e)
        {
            logger.log(LogLevel::ERROR, "Exception in registerObject: " + std::string(e.what()));
            throw;
        }
    }

    // Register a UI element
    void Window::registerUIElement(UI::UIElement element)
    {
        try
        {
            auto ui = std::make_shared<UI::UIElement>(element);
            logger.log(LogLevel::DEBUG, "Registering Ui element with ID: " + ui->id);
            ui->build(this);
            uiElements.push_back(std::move(ui));
        }
        catch (const std::exception &e)
        {
            logger.log(LogLevel::ERROR, "Exception in registerUIElement: " + std::string(e.what()));
            throw;
        }
    }

    // Calculate frame rate
    void Window::CalculateFrameRate()
    {
        try
        {
            static double previousTime = glfwGetTime();
            double currentTime = glfwGetTime();
            double deltaTime = currentTime - previousTime;
            previousTime = currentTime;
            time.setDeltaTime(deltaTime);
            fps = (int)(1.0 / deltaTime);
        }
        catch (const std::exception &e)
        {
            logger.log(LogLevel::ERROR, "Exception in CalculateFrameRate: " + std::string(e.what()));
            throw;
        }
    }

    // Get current frames per second
    int Window::getCurrentFps()
    {
        try
        {
            return fps;
        }
        catch (const std::exception &e)
        {
            logger.log(LogLevel::ERROR, "Exception in getCurrentFps: " + std::string(e.what()));
            throw;
        }
    }

    // Check if window is closed
    bool Window::IsClosed()
    {
        try
        {
            return closed;
        }
        catch (const std::exception &e)
        {
            logger.log(LogLevel::ERROR, "Exception in IsClosed: " + std::string(e.what()));
            throw;
        }
    }

    // Set double buffering option
    void Window::setDobbleBuffering(bool value)
    {
        try
        {
            dobbleBuffering = value;
        }
        catch (const std::exception &e)
        {
            logger.log(LogLevel::ERROR, "Exception in setDobbleBuffering: " + std::string(e.what()));
            throw;
        }
    }

    // Set on type register callback function
    void Window::setOnTypeRegister(std::function<void(Window *)> callback)
    {
        if (callback == nullptr)
        {
            logger.log(LogLevel::ERROR, "OnTypeRegister function cannot be null");
            throw std::invalid_argument("OnTypeRegister function cannot be null");
        }
        onTypeRegister = callback;
    }
    bool Window::isKeyPressed(int key)
    {
        return glfwGetKey(window, key) == GLFW_PRESS;
    }
    void Window::mouse_callback(GLFWwindow *window, double xpos, double ypos)
    {
        try
        {
            Window *self = static_cast<Window *>(glfwGetWindowUserPointer(window));
            self->mouseCallback(self, xpos, ypos);
        }
        catch (const std::exception &e)
        {
            Window *self = static_cast<Window *>(glfwGetWindowUserPointer(window));
            self->logger.log(LogLevel::ERROR, "Exception in framebufferSizeCallback: " + std::string(e.what()));
            throw;
        }
    }
    void Window::close()
    {
        glfwSetWindowShouldClose(window, true);
    }
    void Window::setCamFOV(float fov)
    {
        this->FOV = fov;
        camUpdate();
    }
}
