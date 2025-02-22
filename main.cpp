#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <cstddef>
#include <SGL/window.h>
#include <SGL/object.h>
#include <sstream>
#include <iterator>
#include <fstream>
#include <cmath>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <SGL/SceneManaging/scenemanager.h>
#include <SGL/SceneManaging/scenedata.h>
#include <SGL/SceneManaging/sceneobject.h>
#include <SGL/LayoutManaging/layoutmanager.h>
#include <SGL/LayoutManaging/layoutdata.h>
#include <SGL/LayoutManaging/layoutobject.h>
#include <chrono>
#include <thread>
#include <SGL/gameobjects/cube.h>
#include <SGL/components/TestComponent.h>
#include <SGL/UI/ui-element.h>
#include <SGL/utils/free_fly_cam.h>
using namespace SGL;
FreeFlyCam cam = FreeFlyCam();
SceneData data = SceneData();
LayoutManaging::LayoutData layoutData = LayoutManaging::LayoutData();
UI::UIElement *fovBar;
UI::UIElement *speedBar;
float fov = 45.0f;
void processInput(Window *window)
{
    if (window->isKeyPressed(GLFW_KEY_ESCAPE))
    {
        window->close();
    }
    if (window->isKeyPressed(GLFW_KEY_KP_ADD))
    {
        cam.camSpeed += 10 * window->time.getDeltaTime();
        if (cam.camSpeed > 50)
        {
            cam.camSpeed = 50;
        }
        speedBar->scale = glm::vec2(0.1, cam.camSpeed / 15);
    }
    if (window->isKeyPressed(GLFW_KEY_KP_SUBTRACT))
    {
        cam.camSpeed -= 10 * window->time.getDeltaTime();
        if (cam.camSpeed < 10)
        {
            cam.camSpeed = 10;
        }
        speedBar->scale = glm::vec2(0.1, cam.camSpeed / 15);
    }
    if (window->isKeyPressed(GLFW_KEY_UP))
    {
        fov += 10 * window->time.getDeltaTime();
        if (fov > 100)
        {
            fov = 100;
        }
        fovBar->scale = glm::vec2(fov / 50, 0.1);
        window->setCamFOV(fov);
    }
    if (window->isKeyPressed(GLFW_KEY_DOWN))
    {
        fov -= 10 * window->time.getDeltaTime();
        if (fov < 50)
        {
            fov = 50;
        }
        fovBar->scale = glm::vec2(fov / 50, 0.1);
        window->setCamFOV(fov);
    }
    cam.inputCallback(window);
}
void Update(Window *window)
{
}
void fpsWatch(Window *window)
{
    while (!window->IsClosed())
    {
        int fps = window->getCurrentFps();
        std::cout << "___________________" << std::endl
                  << "FPS: " << fps << std::endl
                  << "DeltaTime: " << window->time.getDeltaTime() << std::endl
                  << "Camera position: (" << window->camera.cameraPos.x << ", " << window->camera.cameraPos.y << ", " << window->camera.cameraPos.z << ")" << std::endl
                  << "Camera rotation: (" << window->camera.rotation.x << ", " << window->camera.rotation.y << ", " << window->camera.rotation.z << ")" << std::endl
                  << "Camera front: (" << window->camera.cameraFront.x << ", " << window->camera.cameraFront.y << ", " << window->camera.cameraFront.z << ")" << std::endl
                  << "Camera speed: " << cam.camSpeed << "\r" << std::flush;
        ;
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    }
}
void createScene()
{
    SceneObject sobj1 = SceneObject();
    Transform t1 = Transform();
    t1.setScaling(glm::vec3(10, 10, 1));
    t1.translate(glm::vec3(0, -5, 0));
    sobj1.transform = t1;
    sobj1.model = "basic/3d/cube";
    sobj1.shader = "default";
    data.addObject(&sobj1);
    sobj1.type = "triangle";
    sobj1.texture = "box.jpg";
    // sobj1.addComponent("TestComponent");
    saveScene(&data, "2d_triangles");
}
void buildLayout()
{
    // fov bar
    LayoutManaging::LayoutObject obj = LayoutManaging::LayoutObject();
    obj.model = "ui/box";
    obj.texture_str = "sgl-logo.jpg";
    obj.id = "ui1";
    obj.position = glm::vec2(0, 1);
    obj.rotation = 0;
    obj.scale = glm::vec2(1, 0.1);
    obj.ZIndex = 1;
    obj.color = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
    layoutData.addObject(&obj);
    // speed bar
    LayoutManaging::LayoutObject obj1 = LayoutManaging::LayoutObject();
    obj1.model = "ui/box";
    obj1.texture_str = "sgl-logo.jpg";
    obj1.id = "ui2";
    obj1.position = glm::vec2(1, 0);
    obj1.rotation = 0;
    obj1.scale = glm::vec2(0.1, 1);
    obj1.ZIndex = 1;
    obj1.color = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
    layoutData.addObject(&obj1);
    LayoutManaging::saveLayout(&layoutData, "basic_layout");
}
void mouseCallback(Window *window, double xpos, double ypos)
{
    cam.mouseCallback(window, xpos, ypos);
}
void onTypeRegister(Window *window)
{
    window->factory.registerObject("cube", []()
                                   { return std::make_shared<SGL::GameObjects::Cube>(); });
    window->factory.registerComponent("TestComponent", []()
                                      { return std::make_shared<SGL::Components::TestComponent>(); });
}
// main
int main(int, char **)
{
    std::cout << R"(
                                     
   _____    _____   _      
  / ____|  / ____| | |     
 | (___   | |  __  | |     
  \___ \  | | |_ | | |     
  ____) | | |__| | | |____ 
 |_____/   \_____| |______|  

    simple game library                         
    )" << std::endl;
    std::cout << "Using sgl version: " << SGL_VERSION << std::endl;
    std::cout << "Using glfw version: " << GLFW_VERSION_MAJOR << "." << GLFW_VERSION_MINOR << "." << GLFW_VERSION_REVISION << std::endl;
    std::cout << "This is a test program\nThis program is designed to test comatibility of sgl engine with your hardware" << std::endl;
    std::cout << "Running on: " << std::endl;
    std::cout << "OS: ";
#ifdef _WIN32
    std::cout << "Windows" << std::endl;
#else
#ifdef __APPLE__
    std::cout << "MacOS" << std::endl;
#else
    std::cout << "Linux" << std::endl;
#endif
#endif
    std::cout << "CPU Architecture: ";
#ifdef __x86_64__
    std::cout << "x64" << std::endl;
#else
    std::cout << "x86" << std::endl;
#endif
    glfwInit();
    glfwWindowHint(GLFW_VISIBLE, GLFW_FALSE);
    GLFWwindow *gwindow = glfwCreateWindow(1, 1, "Headless", NULL, NULL);
    glfwMakeContextCurrent(gwindow);
    gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
    std::cout << "GL: " << glGetString(GL_VERSION) << std::endl;
    std::cout << "GLSL: " << glGetString(GL_SHADING_LANGUAGE_VERSION) << std::endl;
    std::cout << "OpenGL: " << glGetString(GL_RENDERER) << std::endl;
    std::cout << "OpenGL vendor: " << glGetString(GL_VENDOR) << std::endl;
    std::cout << "\n"
              << std::endl;
    std::cout << "Press enter to continue" << std::endl;
    std::cin.get();
    std::cout << "---- Begin of engine init -----" << std::endl;
    glfwTerminate();
    cam.camSpeed = 10;
    // create the window
    Window window = Window(1000, 1000, "SGL", true); // strongly recommended to be set to true, setting it to false may cause graphical issues or window initialization failure
    window.setDobbleBuffering(true);
    // preinit with OpenGL 3.3
    window.preInit(3, 3);
    // set callbacks
    window.setUpdateCallback(Update);
    window.setInputCallback(processInput);
    window.setOnTypeRegister(onTypeRegister);
    window.setMouseCallback(mouseCallback);
    // set double buffering
    // Window init
    window.init();
    // scene loading
    createScene();
    loadSceneByName(&window, "2d_triangles");
    buildLayout();
    LayoutManaging::loadLayoutByName("basic_layout", &window);
    fovBar = window.getUiElementById("ui1");
    speedBar = window.getUiElementById("ui2");
    //  fps
    std::thread th1(fpsWatch, &window);
    // main loop
    window.start();
    // wait for exit
    th1.join();
    return 0;
}
