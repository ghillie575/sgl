#include <SGL/LayoutManaging/layoutobject.h>
using namespace SGL::LayoutManaging;
nlohmann::json LayoutObject::toJson() const {
        nlohmann::json j;
        j["model"] = model;
        j["texture_str"] = texture_str;
        j["id"] = id;
        j["position"] = { position.x, position.y };
        j["rotation"] = rotation;
        j["scale"] = { scale.x, scale.y };
        j["ZIndex"] = ZIndex;
        j["color"] = { color.r, color.g, color.b, color.a };
        return j;
    }
    void LayoutObject::fromJson(const nlohmann::json& j) {
        model = j.at("model").get<std::string>();
        texture_str = j.at("texture_str").get<std::string>();
        id = j.at("id").get<std::string>();
        position = { j.at("position")[0].get<float>(), j.at("position")[1].get<float>() };
        rotation = j.at("rotation").get<float>();
        scale = { j.at("scale")[0].get<float>(), j.at("scale")[1].get<float>() };
        ZIndex = j.at("ZIndex").get<int>();
        color = { j.at("color")[0].get<float>(), j.at("color")[1].get<float>(), 
                  j.at("color")[2].get<float>(), j.at("color")[3].get<float>() };
    }
    SGL::UI::UIElement LayoutObject::build() {
        SGL::UI::UIElement element;
        element.loadModel(model);
        element.loadTexture(texture_str);
        element.setPosition(position);
        element.rotation = rotation;
        element.scale = scale;
        element.ZIndex = ZIndex;
        element.setColor(color);
        element.id = id;
        return element;
    }
