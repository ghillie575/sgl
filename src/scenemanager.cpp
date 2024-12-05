#include <iostream>
#include <nlohmann/json.hpp>
#include <window.h>
#include <sceneobject.h>
#include <scenedata.h>
#include <object.h>
#include <logger.h>
Logger logger = Logger("SceneLoader");
void loadScene(Window* window, std::string json) {
    nlohmann::json sceneJson = nlohmann::json::parse(json);
    Shader shader = Shader("engine/shaders/default.vs", "engine/shaders/default.fs");
    int current = 0;
    int all = sceneJson["count"];
    logger.log(LogLevel::INFO,"loading scene");
    for (const auto& objectJson : sceneJson["objects"]) {
        logger.log(LogLevel::INFO,std::string("loading object: ") + std::to_string(current + 1) + std::string("/") + std::to_string(all));
        SceneObject object = SceneObject();
        object.fromJson(objectJson);
        Object obj = Object();
        obj.setDrawMode(lines);
        obj.loadModel("basic/2d/board");
        obj.useShader(&shader);
        obj.transform = object.transform;
        window->regObject(obj);
        current += 1;
        //object reg to window
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
    return sceneJson.dump();
}