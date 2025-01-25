#ifndef UI_ELEMENT_H
#define UI_ELEMENT_H
#include <vector>
#include <iostream> 
#include <SGL/shader.h>
#include <SGL/window.h>
namespace SGL::UI{

class UIElement{
    public:
        void draw();
        void build(Window* window);
        void loadTexture(std::string texturePath);
        void setColor(glm::vec4 color);
        void setPosition(glm::vec2 position);
        glm::vec2 position;
        int ZIndex;
        std::string model;
        std::string id;
        bool visible = true;
        void loadModel(std::string modelName);
    private:
        Shader* shader = nullptr;
        unsigned int texture;
        Logger logger = Logger("");
        std::string generateRandomID(int length);
        unsigned int VBO, VAO, EBO;
        int polCount;
        glm::vec4 color = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
        std::vector<unsigned int> ind;
        std::vector<float> vert;
        void useShader(const char* shaderName,Window* window);
        void useShader(Shader* shader);
        
        
};

}
#endif