#include <SGL/component.h>
void Component::setProperty(std::string propName, void *value)
{
    properties[propName] = value;
}

void Component::removeProperty(std::string propName)
{
    if (properties.find(propName) != properties.end())
    {
        properties.erase(propName);
    }
}

void *Component::getProperty(std::string propName)
{
    if (properties.find(propName) != properties.end())
    {
        return properties[propName];
    }
    return nullptr;
}
void Component::Start() {}
void Component::Update() {}
Component::Component(std::string name) {
    setProperty<std::string>("type", name);
    logger = Logger(name);

}
std::string Component::toJson() {
    nlohmann::json json;
    json["type"] = *getProperty<std::string>("type");
    return json.dump();
}
Component::Component() {
    setProperty<std::string>("type", "component");
    logger = Logger("component");
}
void Component::fromJson(const nlohmann::json &json) {
    setProperty<std::string>("type", json["type"].get<std::string>());
} 