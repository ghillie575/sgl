#ifndef COMPONENT_H
#define COMPONENT_H
#include <iostream>
#include <SGL/transform.h>
#include <SGL/object.h>
namespace SGL{
class Component
{
private:
    std::unordered_map<std::string, void *> properties;

public:
    Transform *transform;
    GameObject *gameObject;
    Logger logger;
    virtual void Start();
    virtual void Update();
    virtual void prepare();
    void setProperty(std::string propName, void *value);
    template <typename T>
    void setProperty(std::string propName, T value) {
        setProperty(propName, static_cast<void*>(&value));
    }
    std::string toJson();
    void fromJson(const nlohmann::json& json);
    void removeProperty(std::string propName);
    void *getProperty(std::string propName);
    template <typename T>
    T* getProperty(std::string propName) {
        auto it = properties.find(propName);
        if (it != properties.end()) {
            return static_cast<T*>(it->second);
        }
        return nullptr;
    }
    Component(std::string name);
    Component();
};
}
#endif