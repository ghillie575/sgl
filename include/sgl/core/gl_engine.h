#ifndef GL_ENGINE_H
#define GL_ENGINE_H
#include <glad/glad.h>
#include <GLFW/glfw3.h>
class GLEngine
{
public:
    GLEngine();
    int initialize();
    const GLubyte *version;
    const GLubyte *renderer;
    const GLubyte *vendor;
    const GLubyte *shaderV;
};
GLEngine *getEngine();
#endif
