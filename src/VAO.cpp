#include <SGL/VAO.h>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
using namespace SGL;

VAO::VAO()
{
    glGenVertexArrays(1, &ID);
}
void VAO::Destroy()
{
    if (ID == 0)
    {
        return; // Avoid double deletion
    }
    glDeleteVertexArrays(1, &ID);
    ID = 0; // Set ID to 0 after deletion to avoid dangling pointer
}
void VAO::init(std::vector<VertexAttribute> vertexAttributes, int indCount)
{
    this->indCount = indCount;
    int totalSize = 8;
    for (size_t i = 0; i < vertexAttributes.size(); i++)
    {
        totalSize += vertexAttributes[i].size;
    }
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, totalSize * sizeof(float), (void *)0); // Position
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, totalSize * sizeof(float), (void *)(3 * sizeof(float))); // Texture
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, totalSize * sizeof(float), (void *)(5 * sizeof(float))); // Normals
    glEnableVertexAttribArray(2);
    int offset = 8;
    std::sort(vertexAttributes.begin(), vertexAttributes.end(),
              [](const VertexAttribute &a, const VertexAttribute &b)
              {
                  return a.location < b.location;
              });

    for (size_t i = 0; i < vertexAttributes.size(); i++)
    {
        glVertexAttribPointer(vertexAttributes[i].location, vertexAttributes[i].size, GL_FLOAT, GL_FALSE, totalSize * sizeof(float), (void *)(offset * sizeof(float)));
        glEnableVertexAttribArray(vertexAttributes[i].location);
        offset += vertexAttributes[i].size;
    }
}
void VAO::Bind()
{
    glBindVertexArray(ID);
}
void VAO::Unbind()
{
    glBindVertexArray(0);
}
void VAO::Draw()
{
    glDrawElements(GL_TRIANGLES, indCount, GL_UNSIGNED_INT, 0);
}