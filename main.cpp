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

Object obj;
float movespeed = 0.01f;
void processInput(Window *window)
{    if (glfwGetKey(window->window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window->window, true);
}
void Update(Window *window)
{
}

int main(int, char **)
{

    glm::vec4 vec(1.0f, 0.0f, 0.0f, 1.0f);
    glm::mat4 trans = glm::mat4(1.0f);
    trans = glm::translate(trans, glm::vec3(1.0f, 1.0f, 0.0f));
    vec = trans * vec;
    std::cout << vec.x << vec.y << vec.z << std::endl;
    std::cout << "Hello, from XandO!\n";
    Window window = Window(1000, 1000, "2dBox");
    window.Init();
    Shader shader = Shader("engine/shaders/default.vs", "engine/shaders/default.fs");
    obj = Object();
    obj.setDrawMode(lines);
    obj.loadModel("basic/2d/board");
    obj.useShader(shader);
    Object obj1 = Object();
    obj1.setDrawMode(lines);
    obj1.loadModel("basic/2d/triangle");
    obj1.useShader(shader);
    obj1.setScale(glm::vec3(0.2,0.2,0.2));
    glLineWidth(10.0f);
    window.setUpdate(Update);
    window.setInputProcess(processInput);
    window.regObject(obj);
    window.regObject(obj1);
    window.start();
}
