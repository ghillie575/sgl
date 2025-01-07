#include <nlohmann/json.hpp>
#include <transform.h>
#include <object.h>
#ifndef SCENE_OBJECT_H
#define SCENE_OBJECT_H
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
    SceneObject();

    // Add fromJson method to parse JSON data
    void fromJson(const nlohmann::json& json);
    void setObjectName(std::string name);
    // Add toJson method to generate JSON data
    nlohmann::json toJson() const;
    private:
    std::string generateRandomID(int length);
};
#endif