#include <nlohmann/json.hpp>
#include <transform.h>
#include <object.h>
#ifndef SCENE_OBJECT_H
#define SCENE_OBJECT_H
class SceneObject {
public:
    Transform transform;
    std::string model;
    drawAs mode;
    std::string shader;

    // Add fromJson method to parse JSON data
    void fromJson(const nlohmann::json& json);
    // Add toJson method to generate JSON data
    nlohmann::json toJson() const;
};
#endif