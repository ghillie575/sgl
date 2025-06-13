#ifndef TEXTURE_H
#define TEXTURE_H
#include <string>
#include <SGL/logger.h>
namespace SGL
{
    class Texture
    {
    public:
        Logger logger = Logger("");
        int loadTexture(std::string texturePath);
        void useTexture();

    private:
        unsigned int ID;
    };
}

#endif