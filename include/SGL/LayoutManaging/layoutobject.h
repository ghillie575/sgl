#ifndef LAYOUTOBJECT_H
#define LAYOUTOBJECT_H
#include <iostream>
#include <nlohmann/json.hpp>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <SGL/UI/ui-element.h>
namespace SGL::LayoutManaging{
    class LayoutObject{
        
    public:
    // Fields corresponding to UIElement
    std::string model;
    std::string texture_str;
    std::string id;
    glm::vec2 position = glm::vec2(0, 0);
    float rotation = 0.0f;
    glm::vec2 scale = glm::vec2(1, 1);
    int ZIndex = 1;
    glm::vec4 color = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);

    // Method to convert UIElementData to JSON
    nlohmann::json toJson() const ;

    // Method to populate UIElementData from JSON
    void fromJson(const nlohmann::json& j) ;

    // Method to build a UIElement from UIElementData
    SGL::UI::UIElement build();
};
}
#endif