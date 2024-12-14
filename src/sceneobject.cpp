 #include <sceneobject.h>
 void SceneObject::fromJson(const nlohmann::json& json) {
        transform.fromJson(json["transform"]);
        model = json["model"].get<std::string>();
        shader = json["shader"];
        if(json["mode"].dump().compare("ln") == 0){
            mode = lines;
        }else if(json["mode"].dump().compare("trg") == 0){
            mode = triangles;
        }
    }

    // Add toJson method to generate JSON data
    nlohmann::json SceneObject::toJson() const{
        nlohmann::json json;
        if(mode == lines){
            json["mode"] = "ln";
        }else if(mode == triangles){
            json["mode"] = "trg";
        }
        json["transform"] = transform.toJson();
        json["model"] = model;
        json["shader"] = shader;
        return json;
    }