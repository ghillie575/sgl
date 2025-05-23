#ifndef EBO_H
#define EBO_H
#include <vector>
namespace SGL
{
    class EBO
    {
    public:
        unsigned int ID;
        EBO();
        ~EBO();
        void Bind();
        void init(std::vector<unsigned int> indices);
        void Unbind();
        void Destroy();
    };
}
#endif