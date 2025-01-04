#include <iostream>
#include <nlohmann/json.hpp>
#include <window.h>
#include <sceneobject.h>
#include <scenedata.h>
#include <object.h>
#include <logger.h>
#include <fstream>

Logger logger = Logger("\e[36mSceneLoader");

void loadScene(Window* window, const std::string& json) {
    logger = Logger("\e[36mSceneLoader", window->debug);
    logger.log(LogLevel::INFO, "Loading scene");
    try {
        const auto sceneJson = nlohmann::json::parse(json);
        const int all = sceneJson.at("count");
        logger.log(LogLevel::DEBUG, "Loading scene with " + std::to_string(all) + " objects");

        int current = 0;
        for (const auto& objectJson : sceneJson.at("objects")) {
            logger.log(LogLevel::INFO, "Loading object: " + std::to_string(++current) + "/" + std::to_string(all));
            SceneObject object;
            object.fromJson(objectJson);

            logger.log(LogLevel::DEBUG, "Object type: " + object.type);
            logger.log(LogLevel::DEBUG, "Object name: " + object.name);
            logger.log(LogLevel::DEBUG, "Object model: " + object.model);
            logger.log(LogLevel::DEBUG, "Object shader: " + object.shader);
            std::shared_ptr<GameObject> obj = window->factory.createObject(object.type);
            obj->setDrawMode(object.mode);
            obj->loadModel(object.model.c_str());
            obj->useShader(object.shader.c_str());
            obj->transform = object.transform;
            obj->id = object.id;
            obj->name = object.name;
            window->registerObject(obj);
        }
    } catch (const std::exception& e) {
        logger.log(LogLevel::ERROR, "Exception occurred: " + std::string(e.what()));
    }
    logger.log(LogLevel::INFO, "Done");
}

std::string createScene(SceneData* data) {
    logger.log(LogLevel::DEBUG, "Creating scene from data");
    nlohmann::json sceneJson;
    sceneJson["objects"] = nlohmann::json::array();
    sceneJson["count"] = data->getObjectCount();

    for (int i = 0; i < data->getObjectCount(); ++i) {
        const SceneObject* object = data->getObject(i);
        logger.log(LogLevel::DEBUG, "Serializing object: " + object->name);
        sceneJson["objects"].push_back(object->toJson());
    }
    return sceneJson.dump(4);
}

void loadSceneByName(Window* window, const std::string& sceneName) {
    logger.log(LogLevel::INFO, "Loading scene: " + sceneName);
    std::ifstream file("scenes/" + sceneName + ".json");
    if (file) {
        logger.log(LogLevel::DEBUG, "Scene file opened");
        std::stringstream buffer;
        buffer << file.rdbuf();
        loadScene(window, buffer.str());
    } else {
        logger.log(LogLevel::ERROR, "Unable to open scene file: " + sceneName);
    }
}

void saveScene(SceneData* data, const std::string& sceneName) {
    logger.log(LogLevel::INFO, "Saving scene to file: " + sceneName);
    const std::string json = createScene(data);
    std::ofstream file("scenes/" + sceneName + ".json");

    if (file) {
        logger.log(LogLevel::DEBUG, "Scene file opened");
        file << json;
        logger.log(LogLevel::DEBUG, "Scene saved: " + sceneName);
    } else {
        logger.log(LogLevel::ERROR, "Unable to save scene: " + sceneName);
    }
}

