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
#include <SGL/vertex_attribute.h>

#ifndef OBJECT_H
#define OBJECT_H

namespace SGL
{
    class Window;

    // Enum to define the drawing mode
    enum drawAs
    {
        lines,    // Draw as lines
        triangles // Draw as triangles
    };

    class Component;

    // Represents a game object in the scene
    class GameObject
    {
    private:
        bool modelUsesEBO = true; // Indicates if the model uses an Element Buffer Object (EBO)

        unsigned int texture;                                // Texture ID
        Logger logger = Logger("");                          // Logger instance for debugging
        std::string generateRandomID(int length);            // Generates a random ID for the object
        glm::vec4 color = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f); // Object color (RGBA)
        unsigned int VBO, VAO, EBO;                          // OpenGL buffer objects: Vertex Buffer Object, Vertex Array Object, Element Buffer Object

    public:
        std::vector<VertexAttribute> vertexAttributes;      // List of vertex attributes for the object
        bool debug = false;                                 // Debug mode flag
        Window *window = nullptr;                           // Pointer to the associated window
        PhysObject *physObject = nullptr;                   // Pointer to the associated physics object
        std::vector<std::shared_ptr<Component>> components; // List of components attached to the object
        std::string id;                                     // Unique identifier for the object
        std::string name = "x";                             // Name of the object
        Shader *shader = nullptr;                           // Pointer to the shader used by the object
        std::string shaderName = "";                        // Name of the shader
        Material material;                                  // Material properties of the object

        Transform transform;             // Transform properties (position, rotation, scale)
        std::vector<unsigned int> ind;   // Indices for the model
        std::vector<float> vert;         // Vertices for the model
        int polCount;                    // Polygon count

        // Constructor
        GameObject();

        // Builds the object (e.g., initializes buffers)
        virtual void build();

        // Renders the object
        virtual void render(Window *window);

        // Sets the shader by name
        void useShader(const char *shaderName);

        // Sets the shader by pointer
        void useShader(Shader *shader);

        // Frees allocated resources
        void freeResources();

        // Sets the drawing mode

        // Loads a model from a file
        void loadModel(std::string modelName);

        // Prints model data for debugging
        void printModelData();

        // Loads and applies a texture from a file
        void useTexture(std::string texturePath);

        // Sets the color of the object
        void setColor(glm::vec4 color);

        // Starts the object (e.g., initializes components)
        void start(Window *window);

        // Adds a component to the object
        void addComponent(Window *window, std::string type);

        // Retrieves a component of a specific type
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

        // Debugger function for logging object state
        void debugger();
    };
}

#endif