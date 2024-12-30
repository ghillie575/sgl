#include <iostream>
#include <nlohmann/json.hpp>
#include <window.h>
#include <sceneobject.h>
#include <scenedata.h>
#include <object.h>
#include <logger.h>
#include <fstream>
Logger logger = Logger("SceneLoader");
void loadScene(Window* window, std::string json) {
    nlohmann::json sceneJson = nlohmann::json::parse(json);
    int current = 0;
    int all = sceneJson["count"];
    logger.log(LogLevel::INFO,"loading scene");
    for (const auto& objectJson : sceneJson["objects"]) {
        logger.log(LogLevel::INFO,std::string("loading object: ") + std::to_string(current + 1) + std::string("/") + std::to_string(all));
        SceneObject object = SceneObject();
        object.fromJson(objectJson);
        GameObject obj = GameObject();
        obj.setDrawMode(object.mode);
        obj.loadModel(object.model.c_str());
        obj.useShader(object.shader.c_str());
        obj.transform = object.transform;
        obj.id = object.id;
        obj.name = object.name;
        window->regObject(obj);
        current += 1;
    }
}

std::string createScene(SceneData* data) {
    nlohmann::json sceneJson;
    sceneJson["objects"] = nlohmann::json::array();
    sceneJson["count"] = data->getObjectCount();
    for (int i = 0; i < data->getObjectCount(); i++) {
        SceneObject* object = data->getObject(i);
        sceneJson["objects"][i] = object->toJson();
    }
    return sceneJson.dump(4);
}
void loadSceneFromFile(Window* window,std::string sceneName){
    std::ifstream file("scenes/" + sceneName + ".json");
    if (file.is_open()) {
        std::stringstream buffer;
        buffer << file.rdbuf();
        file.close();
        loadScene(window, buffer.str());
    } else {
        logger.log(LogLevel::ERROR, "Unable to open scene file: " + sceneName);
    }
}
void saveScene(SceneData* data, std::string sceneName) {
    std::string json = createScene(data);
    std::ofstream file("scenes/" + sceneName + ".json");
    if (file.is_open()) {
        file << json;
        file.close();
        logger.log(LogLevel::INFO, "Scene saved: " + sceneName);
    } else {
        logger.log(LogLevel::ERROR, "Unable to save scene: " + sceneName);
    }
}