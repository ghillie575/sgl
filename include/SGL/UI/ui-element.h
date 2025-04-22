#ifndef UI_ELEMENT_H
#define UI_ELEMENT_H

#include <vector>
#include <iostream> 
#include <SGL/shader.h>
#include <SGL/window.h>

namespace SGL {
    class Window;
}

namespace SGL::UI {

/**
 * @brief Represents a UI element in the SGL framework.
 * 
 * This class provides functionality for rendering, positioning, and managing
 * UI elements, including texture loading, color setting, and shader usage.
 */
class UIElement {
    public:
        /**
         * @brief Draws the UI element on the screen.
         */
        void draw();

        /**
         * @brief Builds the UI element with the given window context.
         * 
         * @param window Pointer to the window where the UI element will be rendered.
         */
        void build(Window* window);

        /**
         * @brief Loads a texture from the specified file path.
         * 
         * @param texturePath Path to the texture file.
         */
        void loadTexture(std::string texturePath);

        /**
         * @brief Sets the color of the UI element.
         * 
         * @param color RGBA color vector.
         */
        void setColor(glm::vec4 color);

        /**
         * @brief Sets the position of the UI element.
         * 
         * @param position 2D position vector.
         */
        void setPosition(glm::vec2 position);

        // Position of the UI element in 2D space.
        glm::vec2 position = glm::vec2(0, 0);

        // Scale of the UI element.
        glm::vec2 scale = glm::vec2(1, 1);

        // Rotation of the UI element in degrees.
        float rotation = 0.0f;

        // Z-index for rendering order.
        int ZIndex = 1;

        // Model name or identifier for the UI element.
        std::string model;

        // Unique identifier for the UI element.
        std::string id;

        /**
         * @brief Default constructor for the UIElement class.
         */
        UIElement();

        // Visibility flag for the UI element.
        bool visible = true;

        /**
         * @brief Loads a model for the UI element.
         * 
         * @param modelName Name of the model to load.
         */
        void loadModel(std::string modelName);

    private:
        // Transformation matrix for the UI element.
        glm::mat4 model_mat = glm::mat4(1.0f);

        // Pointer to the shader used by the UI element.
        Shader* shader = nullptr;

        // Texture ID for the UI element.
        unsigned int texture;

        // Logger instance for debugging and logging.
        Logger logger = Logger("");

        /**
         * @brief Generates a random ID string of the specified length.
         * 
         * @param length Length of the random ID.
         * @return Generated random ID string.
         */
        std::string generateRandomID(int length);

        // OpenGL buffer objects.
        unsigned int VBO, VAO, EBO;

        // Polygon count for the UI element.
        int polCount;

        // Color of the UI element.
        glm::vec4 color = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);

        // Indices for rendering.
        std::vector<unsigned int> ind;

        // Vertex data for rendering.
        std::vector<float> vert;

        /**
         * @brief Uses a shader by name and associates it with the given window.
         * 
         * @param shaderName Name of the shader to use.
         * @param window Pointer to the window context.
         */
        void useShader(const char* shaderName, Window* window);

        /**
         * @brief Uses the specified shader for rendering.
         * 
         * @param shader Pointer to the shader object.
         */
        void useShader(Shader* shader);

        // Path to the texture file as a string.
        std::string texture_str;
};

} // namespace SGL::UI

#endif