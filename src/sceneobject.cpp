 #include <sceneobject.h>
 void SceneObject::fromJson(const nlohmann::json& json) {
        transform.fromJson(json["transform"]);
        model = json["model"].get<std::string>();
    }

    // Add toJson method to generate JSON data
    nlohmann::json SceneObject::toJson() const{
        nlohmann::json json;
        json["transform"] = transform.toJson();
        json["model"] = model;
        return json;
    }