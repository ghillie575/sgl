#define SGL_DEBUG
#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <cstddef>
#include <window.h>
#include <object.h>
#include <sstream>
#include <iterator>
#include <fstream>
#include <cmath>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <scenemanager.h>
#include <scenedata.h>
#include <sceneobject.h>
GameObject obj;
float movespeed = 0.01f;
void processInput(Window *window)
{
    if (glfwGetKey(window->window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window->window, true);
}
void Update(Window *window)
{
}
//main
int main(int, char **)
{
    /*std::cout << "pre start test. scene manager\n";
    //object creation
    SceneData data = SceneData();
    SceneObject sobj1 = SceneObject();
    SceneObject sobj2 = SceneObject();
    SceneObject sobj3 = SceneObject(); 
    SceneObject sobj4 = SceneObject();
    SceneObject sobj5 = SceneObject();
    SceneObject sobj6 = SceneObject();
    //transorm assigment
    Transform t1 = Transform();
    Transform t2 = Transform();
    Transform t3 = Transform();
    Transform t4 = Transform();
    Transform t5 = Transform();
    Transform t6 = Transform();
    t1.translate(glm::vec3(0, 0, 0));
    t2.translate(glm::vec3(-0.3, 0.3, 0));
    t3.translate(glm::vec3(-0.6, 0.6, 0));
    t4.translate(glm::vec3(0, 0, 0));
    t5.translate(glm::vec3(0.3, 0.3, 0));
    t6.translate(glm::vec3(0.6, 0.6, 0));
    sobj1.transform = t1;
    sobj2.transform = t2;
    sobj3.transform = t3; 
    sobj4.transform = t4;
    sobj5.transform = t5;
    sobj6.transform = t6;
    //model assigment
    sobj1.model = "basic/2d/triangle";
    sobj2.model = "basic/2d/triangle";
    sobj3.model = "basic/2d/triangle";
    sobj4.model = "basic/2d/triangle";
    sobj5.model = "basic/2d/triangle";
    sobj6.model = "basic/2d/triangle";
    //shader assigment
    sobj1.shader = "default";
    sobj2.shader = "default";
    sobj3.shader = "default";
    sobj4.shader = "default";
    sobj5.shader = "default";
    sobj6.shader = "default";
    //object registering
    data.addObject(&sobj1);
    data.addObject(&sobj2);
    data.addObject(&sobj3);
    data.addObject(&sobj4);
    data.addObject(&sobj5);
    data.addObject(&sobj6);
    std::string json = createScene(&data);
    std::cout << json;*/
    std::cout << "Hello, from XandO!\n";
    Window window = Window(1000, 1000, "SGL");
    window.Init();
    //loadScene(&window, json);
    // Shader* shader = window.getShader("default");
    /*obj = Object();
    obj.setDrawMode(lines);
    obj.loadModel("basic/2d/board");
    obj.useShader("default");
    Object obj1 = Object();
    obj1.setDrawMode(lines);
    obj1.loadModel("basic/2d/triangle");
    obj1.useShader("default");
    obj1.transform.setScaling(glm::vec3(0.2,0.2,0.2));
    obj1.transform.translate(glm::vec3(0.1,0.1,0.1));
    glLineWidth(10.0f);


    window.regObject(obj);
    window.regObject(obj1);*/
    loadSceneFromFile(&window,"2d_triangles");
    glLineWidth(10.0f);
    window.setUpdate(Update);
    window.setInputProcess(processInput);
    window.start();
}
