#include <SGL/LayoutManaging/layoutmanager.h>
#include <SGL/logger.h> 
#include <SGL/UI/ui-element.h>
#include <fstream>
SGL::Logger layoutManagerLogger;
namespace SGL::LayoutManaging {
    

void loadLayout(const std::string& json, Window* window) {
    layoutManagerLogger = Logger("\e[36mLayoutLoader", window->debug);
    layoutManagerLogger.log(LogLevel::INFO, "Loading scene");
    try {
        const auto sceneJson = nlohmann::json::parse(json);
        const int all = sceneJson.at("count");
        layoutManagerLogger.log(LogLevel::DEBUG, "Loading scene with " + std::to_string(all) + " objects");

        int current = 0;
        for (const auto& objectJson : sceneJson.at("objects")) {
            layoutManagerLogger.log(LogLevel::INFO, "Loading object: " + std::to_string(++current) + "/" + std::to_string(all));
            LayoutObject object;
            object.fromJson(objectJson);

            layoutManagerLogger.log(LogLevel::DEBUG, "Object model: " + object.model);

                UI::UIElement obj = UI::UIElement();
                obj = object.build();
                window->registerUIElement(obj);
                layoutManagerLogger.log(LogLevel::INFO, "Registered object with ID: " + obj.id);
          
        }
    } catch (const std::exception& e) {
        layoutManagerLogger.log(LogLevel::ERROR, "Exception occurred: " + std::string(e.what()));
    }
    layoutManagerLogger.log(LogLevel::INFO, "Done");
}
std::string createLayout(LayoutData* data) {
    layoutManagerLogger.log(LogLevel::DEBUG, "Creating scene from data");
    nlohmann::json sceneJson;
    sceneJson["objects"] = nlohmann::json::array();
    sceneJson["count"] = data->getObjectCount();

    for (int i = 0; i < data->getObjectCount(); ++i) {
        const LayoutObject* object = data->getObject(i);
        layoutManagerLogger.log(LogLevel::DEBUG, "Serializing object: " + object->id);
        sceneJson["objects"].push_back(object->toJson());
    }
    return sceneJson.dump(4);
}
void loadLayoutByName(std::string layoutName,Window* window) {
    layoutManagerLogger.log(LogLevel::INFO, "Loading layout: " + layoutName);
    std::ifstream file("engine/layouts/" + layoutName + ".json");
    if (file) {
        layoutManagerLogger.log(LogLevel::DEBUG, "Scene file opened");
        std::stringstream buffer;
        buffer << file.rdbuf();
        loadLayout(buffer.str(),window);
    } else {
        layoutManagerLogger.log(LogLevel::ERROR, "Unable to open scene file: " + layoutName);
    }
}
void saveLayout(LayoutData* data, const std::string& layoutName) {
    layoutManagerLogger.log(LogLevel::INFO, "Saving layout to file: " + layoutName);
    const std::string json = createLayout(data);
    std::ofstream file("engine/layouts/" + layoutName + ".json");

    if (file) {
        layoutManagerLogger.log(LogLevel::DEBUG, "Scene file opened");
        file << json;
        layoutManagerLogger.log(LogLevel::DEBUG, "Scene saved: " + layoutName);
    } else {
        layoutManagerLogger.log(LogLevel::ERROR, "Unable to save scene: " + layoutName);
    }
}
}