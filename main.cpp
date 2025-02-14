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
using namespace SGL;
SceneData data = SceneData();
LayoutManaging::LayoutData layoutData = LayoutManaging::LayoutData();
void processInput(Window *window)
{
    
}
void Update(Window *window)
{
}
void fpsWatch(Window* window)
{
    while(!window->IsClosed())
    {
        window->getCurrentFps();
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    }
    
}
void createScene() {
    SceneObject sobj1 = SceneObject();
    Transform t1 = Transform();
    t1.setScaling(glm::vec3(0.1, 0.1, 0.1));
    t1.translate(glm::vec3(0, 0, 0));
    sobj1.transform = t1;
    sobj1.model = "basic/3d/cube";
    sobj1.shader = "default";
    data.addObject(&sobj1);
    sobj1.type = "triangle";
    sobj1.texture = "box.jpg";
    sobj1.addComponent("TestComponent");
    saveScene(&data,"2d_triangles");
}
void buildLayout(){
   LayoutManaging::LayoutObject obj = LayoutManaging::LayoutObject();
   obj.model = "ui/box";
   obj.texture_str = "sgl-logo.jpg";
   obj.id = "ui1";
   obj.position = glm::vec2(1,1);
   obj.rotation = 45;
   obj.scale = glm::vec2(1,1);
   obj.ZIndex = 1;
   obj.color = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
   layoutData.addObject(&obj);
   LayoutManaging::saveLayout(&layoutData,"basic_layout");
}
void onTypeRegister(Window* window){
    window->factory.registerObject("cube", []() { return std::make_shared<SGL::GameObjects::Cube>(); });
    window->factory.registerComponent("TestComponent", []() { return std::make_shared<SGL::Components::TestComponent>(); });
}
//main
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
    std::cout << "This is a test program\nThis program is designed to test comatibility of sgl engine woth your hardware" << std::endl;
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
GLFWwindow* gwindow = glfwCreateWindow(1, 1, "Headless", NULL, NULL);
glfwMakeContextCurrent(gwindow);
gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
    std::cout << "GL: " << glGetString(GL_VERSION) << std::endl;
    std::cout << "GLSL: " << glGetString(GL_SHADING_LANGUAGE_VERSION) << std::endl;
    std::cout << "OpenGL: " << glGetString(GL_RENDERER) << std::endl;
    std::cout << "OpenGL vendor: " << glGetString(GL_VENDOR) << std::endl;
    std::cout << "\n" << std::endl;
    std::cout << "Press enter to continue" << std::endl;
    std::cin.get();
    std::cout << "---- Begin of engine init -----" << std::endl;
    glfwTerminate();
    //create the window
    Window window = Window(1000, 1000, "SGL", true); 
    window.preInit(3,2);
    //set callbacks
    window.setUpdateCallback(Update);
    window.setInputCallback(processInput);
    window.setOnTypeRegister(onTypeRegister);
    //set double buffering
    window.setDobbleBuffering(true);
    //Window init
    window.init();
    //scene loading
    createScene();
    loadSceneByName(&window,"2d_triangles");
    buildLayout();
    LayoutManaging::loadLayoutByName("basic_layout",&window);
    //fps    
    std::thread th1(fpsWatch, &window);
    //main loop
    window.start();
    //wait for exit
    th1.join();
    return 0;
    }

