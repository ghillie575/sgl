#include <vector>
#include <iostream>
#include <SGL/shader.h>
#include <cstddef>
#include <glm/glm.hpp>
#include <SGL/transform.h>
#include <SGL/logger.h>
#include <SGL/component.h>
#include <SGL/window.h>
#include <SGL/material.h>
#include <SGL/physics/phys_object.h>
#ifndef OBJECT_H
#define OBJECT_H
namespace SGL
{
    class Window;
    enum drawAs
    {
        lines,
        triangles
    };
    class Component;
    class GameObject
    {
    private:
        /* data */
        bool modelUsesEBO = true;

        unsigned int texture;
        Logger logger = Logger("");
        std::string generateRandomID(int length);
        glm::vec4 color = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
        unsigned int VBO, VAO, EBO;

    public:
        bool debug = false;
        Window *window = nullptr;
        PhysObject *physObject = nullptr;
        std::vector<std::shared_ptr<Component>> components;
        std::string id;
        std::string name = "x";
        Shader *shader = nullptr;
        std::string shaderName = "";
        Material material;

        Transform transform;
        drawAs mode = drawAs::triangles;
        std::vector<unsigned int> ind;
        std::vector<float> vert;
        int polCount;
        GameObject();
        virtual void build();
        virtual void render(Window *window);
        void useShader(const char *shaderName);
        void useShader(Shader *shader);
        void freeResources();
        void setDrawMode(drawAs mode);
        void loadModel(std::string modelName);
        void printModelData();
        void useTexture(std::string texturePath);
        void setColor(glm::vec4 color);
        void start(Window *window);
        void addComponent(Window *window, std::string type);
        template <typename T>
        T *getComponent()
        {
            if (components.empty()) // Check if the vector is empty
            {
                return nullptr;
            }

            for (int i = 0; i < components.size(); i++)
            {
                std::shared_ptr<Component> component = components[i];
                if (std::dynamic_pointer_cast<T>(component))
                {
                    return std::dynamic_pointer_cast<T>(component).get();
                }
            }
            return nullptr;
        }
        void debugger();
    };
}
#endif