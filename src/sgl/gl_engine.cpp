#include <sgl/core/gl_engine.h>
#include <sgl/logger.h>
#include <sgl/loaders/shader_loader.h>
#include <sgl/loaders/model_loader.h>
#include <sgl/loaders/texture_loader.h>
#include <GLFW/glfw3.h>
GLEngine::GLEngine() {}
int GLEngine::initialize()
{
    if (!glfwInit())
    {
        getLogger()->error("GLEngine", "Failed to initialize GLFW");
        return -1;
    }
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    loadShaderHeaders();
    loadModelHeaders();
    loadTextureHeaders();
    
    getLogger()->log("GLEngine", "OpenGL Engine initialized");
    return 0;
}
GLEngine *engine = new GLEngine(); // Global instance
GLEngine *getEngine()
{
    return engine;
}