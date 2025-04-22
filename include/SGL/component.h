#ifndef COMPONENT_H
#define COMPONENT_H

#include <iostream>
#include <SGL/transform.h>
#include <SGL/object.h>
#include <unordered_map>
#include <string>
#include <nlohmann/json.hpp>

namespace SGL {

/**
 * @brief Base class for all components in the SGL framework.
 * Components are attached to GameObjects and provide specific functionality.
 */
class Component {
private:
    /**
     * @brief A map to store properties associated with the component.
     * The properties are stored as key-value pairs, where the value is a void pointer.
     */
    std::unordered_map<std::string, void *> properties;

public:
    /**
     * @brief Pointer to the Transform associated with the component's GameObject.
     */
    Transform *transform;

    /**
     * @brief Pointer to the GameObject this component is attached to.
     */
    GameObject *gameObject;

    /**
     * @brief Logger instance for logging messages.
     */
    Logger logger;

    /**
     * @brief Virtual method called when the component is initialized.
     * Can be overridden by derived classes.
     */
    virtual void Start();

    /**
     * @brief Virtual method called every frame to update the component.
     * Can be overridden by derived classes.
     */
    virtual void Update();

    /**
     * @brief Virtual method called to prepare the component before use.
     * Can be overridden by derived classes.
     */
    virtual void prepare();

    /**
     * @brief Sets a property for the component.
     * @param propName The name of the property.
     * @param value The value of the property as a void pointer.
     */
    void setProperty(std::string propName, void *value);

    /**
     * @brief Sets a property for the component with a specific type.
     * @tparam T The type of the property value.
     * @param propName The name of the property.
     * @param value The value of the property.
     */
    template <typename T>
    void setProperty(std::string propName, T value) {
        setProperty(propName, static_cast<void*>(&value));
    }

    /**
     * @brief Converts the component's properties to a JSON string.
     * @return A JSON string representing the component's properties.
     */
    std::string toJson();

    /**
     * @brief Populates the component's properties from a JSON object.
     * @param json The JSON object containing the properties.
     */
    void fromJson(const nlohmann::json& json);

    /**
     * @brief Removes a property from the component.
     * @param propName The name of the property to remove.
     */
    void removeProperty(std::string propName);

    /**
     * @brief Retrieves a property value as a void pointer.
     * @param propName The name of the property.
     * @return A void pointer to the property value, or nullptr if not found.
     */
    void *getProperty(std::string propName);

    /**
     * @brief Retrieves a property value with a specific type.
     * @tparam T The type of the property value.
     * @param propName The name of the property.
     * @return A pointer to the property value, or nullptr if not found.
     */
    template <typename T>
    T* getProperty(std::string propName) {
        auto it = properties.find(propName);
        if (it != properties.end()) {
            return static_cast<T*>(it->second);
        }
        return nullptr;
    }

    /**
     * @brief Constructor that initializes the component with a name.
     * @param name The name of the component.
     */
    Component(std::string name);

    /**
     * @brief Default constructor for the component.
     */
    Component();
};

} // namespace SGL

#endif