#include <SGL/EBO.h>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
using namespace SGL;

EBO::EBO()
{
    glGenBuffers(1, &ID);
}

EBO::~EBO()
{
    if (ID != 0) {
        glDeleteBuffers(1, &ID);
        ID = 0;
    }
}

void EBO::Bind()
{
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ID);
}

void EBO::init(std::vector<unsigned int> indices)
{
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ID);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), indices.data(), GL_STATIC_DRAW);
}

void EBO::Unbind()
{
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void EBO::Destroy()
{
    if (ID != 0) {
        glDeleteBuffers(1, &ID);
        ID = 0;
    }
}