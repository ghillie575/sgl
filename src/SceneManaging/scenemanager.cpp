#include <iostream>
#include <nlohmann/json.hpp>
#include <SGL/window.h>
#include <SGL/SceneManaging/sceneobject.h>
#include <SGL/SceneManaging/scenedata.h>
#include <SGL/object.h>
#include <SGL/logger.h>
#include <SGL/SceneManaging/scenemanager.h>
#include <fstream>
using namespace SGL;

Logger sceneManagerLogger = Logger("\e[36mSceneLoader");
void SGL::loadScene(Window *window, const std::string &json)
{
    sceneManagerLogger = Logger("\e[36mSceneLoader", window->debug);
    sceneManagerLogger.log(LogLevel::INFO, "Loading scene");
    try
    {
        const auto sceneJson = nlohmann::json::parse(json);
        const int all = sceneJson.at("count");
        sceneManagerLogger.log(LogLevel::DEBUG, "Loading scene with " + std::to_string(all) + " objects");

        int current = 0;
        for (const auto &objectJson : sceneJson.at("objects"))
        {
            sceneManagerLogger.log(LogLevel::INFO, "Loading object: " + std::to_string(++current) + "/" + std::to_string(all));
            SceneObject object;
            object.fromJson(objectJson);

            sceneManagerLogger.log(LogLevel::DEBUG, "Object type: " + object.type);
            sceneManagerLogger.log(LogLevel::DEBUG, "Object name: " + object.name);
            sceneManagerLogger.log(LogLevel::DEBUG, "Object model: " + object.model);
            sceneManagerLogger.log(LogLevel::DEBUG, "Object shader: " + object.shader);
            sceneManagerLogger.log(LogLevel::DEBUG, "Object material: " + object.material.toJson().dump(4));
            std::shared_ptr<GameObject> obj = window->factory.createObject(object.type);
            if (obj)
            {
                obj->debug = window->debug;
                obj->debugger();
                sceneManagerLogger.log(LogLevel::DEBUG, "Successfully created object of type: " + object.type);
                sceneManagerLogger.log(LogLevel::DEBUG, "Set texture for object: " + object.texture);
                obj->vertexAttributes =object.vertexAttributes;
                obj->loadModel(object.model.c_str());
                sceneManagerLogger.log(LogLevel::DEBUG, "Loaded model for object: " + object.name);
                obj->useShader(object.shader.c_str());
                sceneManagerLogger.log(LogLevel::DEBUG, "Applied shader for object: " + object.name);
                obj->transform = Transform(object.transform);
                obj->id = std::string(object.id);
                obj->material = Material(object.material);
                obj->name = std::string(object.name);
                obj->physObject->properties = PhysProperties(object.properties);
                obj->useTexture(object.texture);
                for (const auto &component : object.components)
                {
                    obj->addComponent(window, component);
                }

                window->registerObject(obj);
                sceneManagerLogger.log(LogLevel::INFO, "Registered object with ID: " + obj->id);
            }
            else
            {
                sceneManagerLogger.log(LogLevel::ERROR, "Failed to create object of type: " + object.type);
            }
        }
    }
    catch (const std::exception &e)
    {
        sceneManagerLogger.log(LogLevel::ERROR, "Exception occurred: " + std::string(e.what()));
    }
    sceneManagerLogger.log(LogLevel::INFO, "Done");
}

std::string SGL::createScene(SceneData *data)
{
    sceneManagerLogger.log(LogLevel::DEBUG, "Creating scene from data");
    nlohmann::json sceneJson;
    sceneJson["objects"] = nlohmann::json::array();
    sceneJson["count"] = data->getObjectCount();

    for (int i = 0; i < data->getObjectCount(); ++i)
    {
        const SceneObject *object = data->getObject(i);
        sceneManagerLogger.log(LogLevel::DEBUG, "Serializing object: " + object->name);
        sceneJson["objects"].push_back(object->toJson());
    }
    return sceneJson.dump(4);
}

void SGL::loadSceneByName(Window *window, const std::string &sceneName)
{
    sceneManagerLogger.log(LogLevel::INFO, "Loading scene: " + sceneName);
    std::ifstream file("scenes/" + sceneName + ".json");
    if (file)
    {
        sceneManagerLogger.log(LogLevel::DEBUG, "Scene file opened");
        std::stringstream buffer;
        buffer << file.rdbuf();
        SGL::loadScene(window, buffer.str());
    }
    else
    {
        sceneManagerLogger.log(LogLevel::ERROR, "Unable to open scene file: " + sceneName);
    }
}

void SGL::saveScene(SceneData *data, const std::string &sceneName)
{
    sceneManagerLogger.log(LogLevel::INFO, "Saving scene to file: " + sceneName);
    const std::string json = SGL::createScene(data);
    std::ofstream file("scenes/" + sceneName + ".json");

    if (file)
    {
        sceneManagerLogger.log(LogLevel::DEBUG, "Scene file opened");
        file << json;
        sceneManagerLogger.log(LogLevel::DEBUG, "Scene saved: " + sceneName);
    }
    else
    {
        sceneManagerLogger.log(LogLevel::ERROR, "Unable to save scene: " + sceneName);
    }
}
