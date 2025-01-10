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
#include <SGL/scenemanager.h>
#include <SGL/scenedata.h>
#include <SGL/sceneobject.h>
#include <chrono>
#include <thread>
#include <SGL/gameobjects/cube.h>  
#include <SGL/components/TestComponent.h>
SceneData data = SceneData();
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
    sobj1.type = "cube";
    sobj1.addComponent("TestComponent");
    saveScene(&data,"2d_triangles");
}
void onTypeRegister(Window* window){
    window->factory.registerObject("cube", []() { return std::make_shared<Cube>(); });
    window->factory.registerComponent("TestComponent", []() { return std::make_shared<TestComponent>(); });
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
    std::cout << "Using sgl " << SGL_VERSION << std::endl;
    //create the window
    Window window = Window(1000, 1000, "SGL", true); 
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
    //fps    
    std::thread th1(fpsWatch, &window);
    //main loop
    window.start();
    //wait for exit
    th1.join();
    return 0;
    }

