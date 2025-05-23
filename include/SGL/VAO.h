#ifndef VAO_H
#define VAO_H
#include <vector>
#include <SGL/vertex_attribute.h>
namespace SGL
{
    class VAO
    {
    private:
        int indCount = 0;

    public:
        unsigned int ID;
        VAO();
        void init(std::vector<VertexAttribute> vertexAttributes, int indCount);
        void Bind();
        void Unbind();
        void Draw();
        void Destroy();
    };
}

#endif