#ifndef LAYOUTOBJECT_H
#define LAYOUTOBJECT_H

#include <iostream>
#include <nlohmann/json.hpp>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <SGL/UI/ui-element.h>
#include <SGL/vertex_attribute.h>
namespace SGL::LayoutManaging
{

    /**
     * @brief Represents a layout object that holds data for UI elements.
     *
     * This class is used to manage the properties of a UI element, such as its
     * position, scale, rotation, color, and other attributes. It also provides
     * methods to serialize and deserialize the object to/from JSON, and to build
     * a UIElement from the stored data.
     */
    class LayoutObject
    {
    public:
        // Fields corresponding to UIElement

        /**
         * @brief The model associated with the UI element.
         */
        std::string model;

        /**
         * @brief The texture string associated with the UI element.
         */
        std::string texture_str;

        /**
         * @brief The unique identifier for the UI element.
         */
        std::string id;

        /**
         * @brief The position of the UI element in 2D space.
         */
        glm::vec2 position = glm::vec2(0, 0);

        /**
         * @brief The rotation of the UI element in degrees.
         */
        float rotation = 0.0f;

        /**
         * @brief The scale of the UI element in 2D space.
         */
        glm::vec2 scale = glm::vec2(1, 1);
        std::string shader = "ui";
        std::vector<VertexAttribute> vertexAttributes;
        /**
         * @brief The Z-index of the UI element, used for rendering order.
         */
        int ZIndex = 1;

        /**
         * @brief The color of the UI element, represented as an RGBA vector.
         */
        glm::vec4 color = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);

        /**
         * @brief Converts the LayoutObject data to a JSON object.
         *
         * @return A JSON object representing the LayoutObject data.
         */
        nlohmann::json toJson() const;
        void addVertexAttribute(int size, int location)
        {
            vertexAttributes.push_back(VertexAttribute(size, location));
        }
        /**
         * @brief Populates the LayoutObject data from a JSON object.
         *
         * @param j The JSON object containing the data.
         */
        void fromJson(const nlohmann::json &j);

        /**
         * @brief Builds a UIElement object from the LayoutObject data.
         *
         * @return A UIElement object initialized with the LayoutObject data.
         */
        SGL::UI::UIElement build();
    };

}

#endif