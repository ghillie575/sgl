#include <nlohmann/json.hpp>
#include <SGL/transform.h>
#include <SGL/object.h>
#include <SGL/component.h>
#ifndef SCENE_OBJECT_H
#define SCENE_OBJECT_H
namespace SGL{
class SceneObject {
public:
    Transform transform;
    std::string model;
    drawAs mode = triangles;
    std::string shader;
    std::string id;
    std::string name = "x";
    std::string type = "default";
    std::string texture = "blank.jpg";
    std::vector<std::string> components;
    SceneObject();
    void addComponent(std::string type); 
    // Add fromJson method to parse JSON data
    void fromJson(const nlohmann::json& json);
    void setObjectName(std::string name);
    // Add toJson method to generate JSON data
    nlohmann::json toJson() const;
    private:
    std::string generateRandomID(int length);
       
};
}
#endif