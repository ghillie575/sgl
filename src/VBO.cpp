#include <SGL/VBO.h>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
using namespace SGL;

VBO::VBO()
{
    glGenBuffers(1, &ID);
}

void VBO::init(std::vector<float> verticies)
{
    glBindBuffer(GL_ARRAY_BUFFER, ID);
    glBufferData(GL_ARRAY_BUFFER, verticies.size() * sizeof(float), verticies.data(), GL_STATIC_DRAW);
}

void VBO::Bind()
{
    glBindBuffer(GL_ARRAY_BUFFER, ID);
}

void VBO::Unbind()
{
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void VBO::Destroy()
{
    if (ID == 0)
    {
        return; // Avoid double deletion
    }
    glDeleteBuffers(1, &ID);
    ID = 0; // Set ID to 0 after deletion to avoid dangling pointer
}