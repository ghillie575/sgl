#define _SGL_DEBUG_
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
GameObject obj;
float movespeed = 0.01f;
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
//main
int main(int, char **)
{
    std::cout << "pre start test. scene manager\n";
    //object creation
    SceneData data = SceneData();
    SceneObject sobj1 = SceneObject();
    SceneObject sobj2 = SceneObject();
    SceneObject sobj3 = SceneObject(); 
    SceneObject sobj5 = SceneObject();
    SceneObject sobj6 = SceneObject();
    //transorm assigment
    Transform t1 = Transform();
    t1.setScaling(glm::vec3(0.1, 0.1, 0.1));
    Transform t2 = Transform();
    t2.setScaling(glm::vec3(0.1, 0.1, 0.1));
    Transform t3 = Transform();
    t3.setScaling(glm::vec3(0.1, 0.1, 0.1));
    Transform t5 = Transform();
    t5.setScaling(glm::vec3(0.1, 0.1, 0.1));
    Transform t6 = Transform();
    t6.setScaling(glm::vec3(0.1, 0.1, 0.1));

    t1.translate(glm::vec3(0, 0, 0));
    t1.setRotation(glm::vec3(0, 0,45));
    t2.translate(glm::vec3(-0.15, 0.15, 0));
    t3.translate(glm::vec3(-0.3, 0.3, 0));
    t5.translate(glm::vec3(0.15, 0.15, 0));
    t6.translate(glm::vec3(0.3, 0.3, 0));
    sobj1.transform = t1;
    sobj2.transform = t2;
    sobj3.transform = t3; 
    sobj5.transform = t5;
    sobj6.transform = t6;
    //model assigment
    sobj1.model = "basic/3d/cube";
    sobj2.model = "basic/3d/cube";
    sobj3.model = "basic/3d/cube";
    sobj5.model = "basic/3d/cube";
    sobj6.model = "basic/3d/cube";
    //shader assigment
    sobj1.shader = "default";
    sobj2.shader = "default";
    sobj3.shader = "default";
    sobj5.shader = "default";
    sobj6.shader = "default";
    //object registering
    data.addObject(&sobj1);
    //data.addObject(&sobj2);
    //data.addObject(&sobj3);
    //data.addObject(&sobj5);
    //data.addObject(&sobj6);

    //below

    SceneObject sobj8 = SceneObject();
    SceneObject sobj9 = SceneObject(); 
    SceneObject sobj11 = SceneObject();
    SceneObject sobj12 = SceneObject();
    //transorm assigment
    Transform t8 = Transform();
    t8.setScaling(glm::vec3(0.1, 0.1, 0.1));
    Transform t9 = Transform();
    t9.setScaling(glm::vec3(0.1, 0.1, 0.1));
    Transform t11 = Transform();
    t11.setScaling(glm::vec3(0.1, 0.1, 0.1));
    Transform t12 = Transform();
    t12.setScaling(glm::vec3(0.1, 0.1, 0.1));
    t8.translate(glm::vec3(-0.15, -0.15, 0));
    t9.translate(glm::vec3(-0.3, -0.3, 0));
    t11.translate(glm::vec3(0.15, -0.15, 0));
    t12.translate(glm::vec3(0.3, -0.3, 0));
    t8.rotate(glm::vec3(180,0,0));
    t9.rotate(glm::vec3(180,0,0));
    t11.rotate(glm::vec3(180,0,0));
    t12.rotate(glm::vec3(180,0,0));
    sobj8.transform = t8;
    sobj9.transform = t9;
    sobj11.transform = t11; 
    sobj12.transform = t12;
    //model assigment
    sobj8.model = "basic/3d/cube";
    sobj9.model = "basic/3d/cube";
    sobj11.model = "basic/3d/cube";
    sobj12.model = "basic/3d/cube";
    sobj1.type = "cube";
    sobj2.type = "cube";
    sobj3.type = "cube";
    sobj5.type = "cube";
    sobj6.type = "cube";
    sobj8.type = "cube";
    sobj9.type = "cube";
    sobj11.type = "cube";
    sobj12.type = "cube";
    //shader assigment
    sobj8.shader = "default";
    sobj9.shader = "default";
    sobj11.shader = "default";
    sobj12.shader = "default";
    //object registering
    //data.addObject(&sobj8);
    //data.addObject(&sobj9);
    //data.addObject(&sobj11);
    //data.addObject(&sobj12);
    std::string json = createScene(&data);
    std::cout << json;
    std::cout << "Hello, from XandO!\n";
    Window window = Window(1000, 1000, "SGL",true);
    window.setDobbleBuffering(true);
    window.init();
    window.factory.registerObjectCreationFunction("cube", []() { return std::make_shared<Cube>(); });
    /*
    //loadScene(&window, json);
    // Shader* shader = window.getShader("default");
    auto obj1 = window.factory.createObject("default");
    obj1->setDrawMode(triangles);
    obj1->loadModel("basic/2d/triangle");
    obj1->useShader("default");
    obj1->transform.translate(glm::vec3(0.1,0.1,0.1));
    glLineWidth(10.0f);


    window.registerObject(obj1);*/
    saveScene(&data,"2d_triangles");
    loadSceneByName(&window,"2d_triangles");
    glLineWidth(10.0f);
    window.setUpdateCallback(Update);
    window.setInputCallback(processInput);
    
    std::thread th1(fpsWatch, &window);
    window.start();
    th1.join();
    return 0;
    }

