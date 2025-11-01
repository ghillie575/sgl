#include <sgl/core/gl_engine.h>
#include <sgl/loaders/shader_loader.h>
#include <sgl/loaders/model_loader.h>
#include <sgl/loaders/texture_loader.h>
#include <sgl/core/gameobject.h>
#include <sgl/window.h>
#include <sgl/logger.h>
#include <sgl/utils.h>
#include <sgl/debug/debug_label.h>
#include <thread>
#include <chrono>
#include <iostream>
#include <sstream>
#include <iomanip>
std::string cShader = "default_tex";
std::string cModel = "square";
std::string cTexture = "blank.png";
Window *window; // Make window global to be accessible in main
Shader *shader;
Model *model;
Texture *texture;
GameObject *gameObject;
std::thread *t;
DebugLabel *label;
unsigned int VBO, VAO, EBO;
int initialize()
{
    if (getEngine()->initialize() != 0)
    {
        std::cerr << "Failed to initialize OpenGL Engine" << std::endl;
        return -1;
    }

    Window *mwindow = new Window(800, 600, "SGl");
    if (mwindow->init() != 0)
    {
        std::cerr << "Failed to initialize window" << std::endl;
        return -1;
    }
    window = mwindow; // Assign to global pointer
    setWindowPointer(mwindow);
    return 0;
}
bool advanced = false;
bool f12Pressed = false;

void processInput(GLFWwindow *glfwWindow)
{
    if (glfwGetKey(glfwWindow, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(glfwWindow, true);

    // --- F12 toggle ---
    if (glfwGetKey(glfwWindow, GLFW_KEY_F12) == GLFW_PRESS)
    {
        if (!f12Pressed)
        {
            advanced = !advanced;
            f12Pressed = true;
        }
    }
    else
    {
        f12Pressed = false;
    }
}

void monitorFps()
{
    while (window->isRunning())
    {
        std::this_thread::sleep_for(std::chrono::milliseconds(100));

        double fps = window->getFps();
        double delta = window->getDeltaTime();

        std::ostringstream oss;
        oss << std::fixed << std::setprecision(6);

        oss << "Fps: " << fps << "\nDelta: " << delta;

        if (advanced)
        {
            // --- Add more info ---
            int width = getWindowPointer()->width;
            int height = getWindowPointer()->height;

            // CPU info (platform-dependent)
#ifdef _WIN32
            SYSTEM_INFO sysInfo;
            GetSystemInfo(&sysInfo);
            unsigned int cores = sysInfo.dwNumberOfProcessors;
#else
            unsigned int cores = std::thread::hardware_concurrency();
#endif

            oss << "\nResolution: " << width << "x" << height;
            oss << " | Cores: " << cores;
            oss << "\nGPU: " << (getEngine()->renderer ? (const char *)getEngine()->renderer : "Unknown");
            oss << "\nVendor: " << (getEngine()->vendor ? (const char *)getEngine()->vendor : "Unknown");
            oss << "\nGL: " << (getEngine()->version ? (const char *)getEngine()->version : "Unknown");
            oss << " | GLSL: " << (getEngine()->shaderV ? (const char *)getEngine()->shaderV : "Unknown");
        }

        label->setText(oss.str());
    }
}
void start()
{
    gameObject = createGameObject(cModel, cShader, cTexture);
    gameObject->setPosition(glm::vec3(0, 0, -1));
    label = createDebugLabel("",0.02,0.95,0.3);
    t = new std::thread(monitorFps);
}
bool back = false;

void update()
{
    processInput(window->window);
    gameObject->render();
    label->render();
    glm::vec3 pos = gameObject->getPosition();
    glm::vec3 rot = gameObject->getRotation();
    if (back)
    {
        pos.x = pos.x - 1 * getWindowPointer()->getDeltaTime();
    }
    else
    {
        pos.x = pos.x + 1 * getWindowPointer()->getDeltaTime();
    }
    if (pos.x > 0.5)
    {
        back = true;
    }
    if (pos.x < -0.5)
    {
        back = false;
    }
    float time = glfwGetTime();
    float s = 1.0f + sin(time * 3.0f) * 0.2f;
    gameObject->setScale(glm::vec3(s, s, 1.0f));
    float x = cos(time) * 0.5f;
    gameObject->setPosition(glm::vec3(x, 0, -1.0f));
    float zRot = sin(time * 2.0f) * glm::radians(45.0f); // ±45°
    gameObject->setRotation(glm::vec3(0.0f, 0.0f, zRot));
}

int main()
{
    setDebugMode(false); // Enable debug mode for detailed logging
    getLogger()->log("Main", "Starting application");
    if (initialize() != 0)
    {
        return -1;
    }
    
    // make sure required resources are loaded
    require(cShader, ResourceType::RESOURCE_SHADER);
    require(cModel, ResourceType::RESOURCE_MODEL);
    require(cTexture, ResourceType::RESOURCE_TEXTURE);
    // start fps watch thead
    //  set callbacks
    window->setOnStartCallback(start);
    window->setOnUpdateCallback(update);
    // config
    window->setFpsLimit(100);
    // start main loop
    window->start();
    // cleanup and exit
    t->join();
    window->cleanup();
    getLogger()->log("Main", "Exiting application");
    return 0;
}
