#include <window.h>
#include <iostream>
#include <filesystem>
namespace fs = std::filesystem;
Window::Window(int height, int width, const char *title)
{
        this->height = height;
        this->width = width;
        this->title = title;
}
void Window::framebuffer_size_callback(GLFWwindow *window, int width, int height)
{
        glViewport(0, 0, width, height);
        logger.log(LogLevel::INFO, "Framebuffer size callback");
}
GameObject *Window::getObject(int id)
{
        for (size_t i = 0; i < objects.size(); i++)
        {
                
        }
        
}
void getAllFiles(const fs::path &directory, std::vector<fs::path> &files, int &fileCOunt)
{
        // Iterate through the directory and its subdirectories
        for (const auto &entry : fs::recursive_directory_iterator(directory))
        {
                if (fs::is_regular_file(entry))
                {
                        files.push_back(entry.path());
                }
        }
}
void Window::Init()
{
        logger.log(LogLevel::INFO, "Initializing window");
        glfwInit();
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
        const GLFWvidmode *mode = glfwGetVideoMode(glfwGetPrimaryMonitor());
        window = glfwCreateWindow(width, height, title, NULL, NULL);
        if (window == NULL)
        {
                std::cout << "Engine init failed:\nFailed to create GLFW window\nat Window::Init()" << std::endl;
                logger.log(LogLevel::ERROR, "Failed to create GLFW window");
                glfwTerminate();
                exit(-1);
        }
        glfwMakeContextCurrent(window);
        if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
        {
                std::cout << "Engine init failed:\nFailed to initialize GLAD\nat Window::Init()" << std::endl;
                logger.log(LogLevel::ERROR, "Failed to initialize GLAD");
                exit(-1);
        }
        logger.log(LogLevel::INFO, "Loading shaders");
        std::vector<fs::path> files;
        int count;
        getAllFiles("engine/shaders", files, count);

        for (const auto &file : files)
        {

                if (file.extension() == ".vs")
                {
                        logger.log(LogLevel::INFO, std::string("Loading shader: ") + file.stem().string());
                        Shader current = Shader(file.string().c_str(), (file.parent_path().string() + std::string("/") + file.stem().string() + ".fs").c_str());
                        shadreReg[file.stem().string()] = current;
                }
        }
}
bool Window::shaderExists(const std::string &shaderName)
{
        return shadreReg.find(shaderName) != shadreReg.end();
}
Shader *Window::getShader(std::string shaderName)
{
        if (shaderExists(shaderName))
        {
                return &shadreReg[shaderName];
        }
        else
        {
                return &shadreReg["default"];
        }
}
void Window::start()
{       
        while (!glfwWindowShouldClose(window))
        {
                // processInput(window);
                Input(this);
                glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
                glClear(GL_COLOR_BUFFER_BIT);
                for (int i = 0; i < objects.size(); i++)
                {
                        objects[i].render();
                }

                update(this);
                glfwSwapBuffers(window);
                glfwPollEvents();
        }
        logger.log(LogLevel::INFO, "Terminating window");
        logger.log(LogLevel::INFO, "Cleaning up");
        for (int i = 0; i < objects.size(); i++)
        {
                

                objects[i].freeResources();
        }
        glfwTerminate();
        logger.log(LogLevel::INFO, "Window terminated");
        return;
}
void Window::setUpdate(void (*func)(Window *window))
{
        update = func;
}
void Window::setInputProcess(void (*func)(Window *window))
{
        Input = func;
}
void Window::regObject(GameObject obj)
{       
        if(obj.shader == nullptr){
        obj.useShader(getShader(obj.shaderName));
        }
        obj.build();
        objects.insert(objects.begin(), obj);
}