#ifndef WINDOW_H
#define WINDOW_H
#define SGL_VERSION "V0.1.2"
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
class Window
{
private:
    int height;
    int width;
    std::string title;
    int fps;
    GLFWwindow *window;
    std::unordered_map<std::string, Shader> shaderRegistry;
    std::vector<std::shared_ptr<GameObject>> objects;
    Logger logger;
    std::function<void(Window*)> updateCallback;
    std::function<void(Window*)> inputCallback;
    std::function<void(Window*)> onTypeRegister;
    void camInit();
    void camUpdate();
    static void framebufferSizeCallback(GLFWwindow *window, int width, int height);
   void CalculateFrameRate();
   bool closed = true;
   bool dobbleBuffering = true;

public:
    bool debug = false;
    Camera camera;
    Time time = Time();
    ObjectFactory factory;
    Window(int height, int width, const char *title);
    Window(int height, int width, const char *title, bool debug);
    void init();
    void setUpdateCallback(std::function<void(Window*)> callback);
    void setInputCallback(std::function<void(Window*)> callback);
    void registerObject(std::shared_ptr<GameObject> obj);
    GameObject* getObjectById(const std::string& id);
    GameObject* getObjectByName(const std::string& name);
    Shader* getShader(const std::string& shaderName);
    bool shaderExists(const std::string &shaderName);
    int getCurrentFps();
    bool IsClosed();
    void start();
    void setDobbleBuffering(bool value);
    void setOnTypeRegister(std::function<void(Window*)> callback);
    
};
#endif
