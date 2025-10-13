#include <sgl/engine/gl_engine.h>
#include <sgl/logger.h>
#include <sgl/engine/shader_loader.h>
#include <GLFW/glfw3.h>
GLEngine::GLEngine() {}
void GLEngine::initialize() {
    if (!glfwInit()) {
        getLogger()->error("GLEngine", "Failed to initialize GLFW");
        return;
    }
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    loadShaderHeaders();
    getLogger()->log("GLEngine", "OpenGL Engine initialized");
}
GLEngine* engine = new GLEngine(); // Global instance
GLEngine* getEngine() {
    return engine;
}