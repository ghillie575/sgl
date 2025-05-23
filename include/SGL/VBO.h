#ifndef VBO_H
#define VBO_H
#include <vector>
namespace SGL{
    class VBO{
        public:
            unsigned int ID;
            VBO();
            void init(std::vector<float> verticies);
            void Bind();
            void Unbind();
            void Destroy();
    };
}
#endif