#ifndef COMPONENT_H
#define COMPONENT_H
#include <iostream>
#include <SGL/transform.h>
#include <SGL/object.h>
class Component
{
private:
    std::unordered_map<std::string, void *> properties;

public:
    Transform *transform;
    GameObject *gameObject;
    void Start();
    void Update();
    void setProperty(std::string propName, void *value);
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
};
#endif