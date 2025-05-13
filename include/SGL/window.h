#ifndef WINDOW_H
#define WINDOW_H

// Define the version of the SGL library
#define SGL_VERSION "main-stable-V0.1.5"

// Include necessary libraries and headers
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <SGL/object.h>
#include <vector>
#include <unordered_map>
#include <string>
#include <functional>
#include <SGL/logger.h>
#include <SGL/time_utils.h>
#include <SGL/objectfactory.h>
#include <SGL/camera.h>
#include <SGL/UI/ui-element.h>
#include <SGL/libraryloader.h>
#include <SGL/lightning/enviroment.h>
#include <SGL/physics/physics_world.h>

namespace SGL
{
    namespace UI
    {
        class UIElement; // Forward declaration of UIElement
    }

    // The Window class represents a graphical window and its associated functionality.
    class Window
    {
    private:
        int height; // Height of the window
        int width; // Width of the window
        std::string title; // Title of the window
        int fps; // Current frames per second
        GLFWwindow *window; // Pointer to the GLFW window
        std::unordered_map<std::string, Shader> shaderRegistry; // Registry of shaders
        std::vector<std::shared_ptr<GameObject>> objects; // List of registered game objects
        std::vector<std::shared_ptr<UI::UIElement>> uiElements; // List of registered UI elements
        Logger logger; // Logger instance for logging
        std::function<void(Window *)> updateCallback; // Callback for update logic
        std::function<void(Window *)> inputCallback; // Callback for input handling
        std::function<void(Window *)> onTypeRegister; // Callback for type registration
        std::function<void(Window *, double, double)> mouseCallback; // Callback for mouse events
        bool closed = true; // Indicates if the window is closed
        float FOV = 50.0f; // Field of view for the camera
        bool dobbleBuffering = true; // Double buffering flag

        // Initializes the camera
        void camInit();

        // Updates the camera
        void camUpdate();

        // Callback for handling window resize events
        static void framebufferSizeCallback(GLFWwindow *window, int width, int height);

        // Callback for handling mouse movement
        static void mouse_callback(GLFWwindow *window, double xpos, double ypos);

        // Calculates the current frame rate
        void CalculateFrameRate();

    public:
        PhysicsWorld *physicsWorld; // Pointer to the physics world
        bool debug = false; // Debug mode flag
        Camera camera; // Camera instance
        Time time = Time(); // Time utility instance
        Lightning::Enviroment lightEnv; // Lighting environment
        ObjectFactory factory; // Object factory for creating game objects

        // Constructor to initialize the window
        Window(int height, int width, const char *title);

        // Constructor to initialize the window with debug mode
        Window(int height, int width, const char *title, bool debug);

        // Unlocks the cursor
        void unlockCursor();
        void lockCursor();

        // Checks if a specific key is pressed
        bool isKeyPressed(int key);

        // Closes the window
        void close();

        // Sets the camera's field of view
        void setCamFOV(float fov);

        // Updates the shaders
        void shaderUpdate();

        // Initializes the window
        void init();

        // Pre-initializes the window
        void preInit();

        // Pre-initializes the window with specific OpenGL version
        void preInit(int glVersionMajor, int glVersionMinor);

        // Sets the update callback
        void setUpdateCallback(std::function<void(Window *)> callback);

        // Sets the input callback
        void setInputCallback(std::function<void(Window *)> callback);

        // Sets the mouse callback
        void setMouseCallback(std::function<void(Window *, double, double)> callback);

        // Registers a game object
        void registerObject(std::shared_ptr<GameObject> obj);

        // Registers a UI element
        void registerUIElement(UI::UIElement element);

        // Retrieves a game object by its ID
        GameObject *getObjectById(const std::string &id);

        // Retrieves a UI element by its ID
        UI::UIElement *getUiElementById(const std::string &id);

        // Retrieves a game object by its name
        GameObject *getObjectByName(const std::string &name);

        // Retrieves a shader by its name
        Shader *getShader(const std::string &shaderName);

        // Checks if a shader exists
        bool shaderExists(const std::string &shaderName);

        // Gets the current frames per second
        int getCurrentFps();

        // Checks if the window is closed
        bool IsClosed();

        // Starts the main loop of the window
        void start();

        // Sets the double buffering flag
        void setDobbleBuffering(bool value);

        // Sets the callback for type registration
        void setOnTypeRegister(std::function<void(Window *)> callback);
    };
}

#endif
