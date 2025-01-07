#include <component.h>
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