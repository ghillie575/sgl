#ifndef OBJECTFACTORY_H
#define OBJECTFACTORY_H
#include <map>
#include <string>
#include <memory>
#include <functional>
#include <SGL/object.h>
#include <SGL/component.h>  
#include <SGL/logger.h>
/**
 * @class ObjectFactory
 * @brief A factory class for creating GameObject instances.
 *
 * This class allows registering creation functions for different types of 
 * GameObjects and creating instances of those objects when needed.
 */
namespace SGL{
class Component;
class ObjectFactory {
private:
    Logger logger = Logger("\e[36mTYPE");
public:
     void freeResources() {
    if (!creationFunctions.empty()) {
        for (auto& entry : creationFunctions) {
            if (entry.second) {
            }
        }
        
        creationFunctions.clear();
    }
    if (componentFunctions.empty()) {
        for (auto& entry : componentFunctions) {
            if (entry.second) {
            }
        }
        
        componentFunctions.clear();
    }
}
    ~ObjectFactory() {
    }
    /**
     * @brief Register a new object creation function with the factory.
     *
     * @tparam T The type of the creation function.
     * @param objectType The type identifier for the object.
     * @param creationFunction The function to create an object of the specified type.
     *
     * @note The creation function must return a std::shared_ptr<GameObject>.
     */
    template <typename T>
    void registerObject(const std::string& objectType, T&& creationFunction) {
        static_assert(std::is_invocable_r_v<std::shared_ptr<GameObject>, T>, 
                      "creationFunction must return std::shared_ptr<GameObject>");
                      
        creationFunctions.emplace(objectType, std::forward<T>(creationFunction));
        logger.log(LogLevel::INFO, "Registered object type: " + objectType);
    }

    /**
     * @brief Create a new object of the specified type.
     *
     * @param objectType The type identifier for the object to create.
     * @return A shared pointer to the created GameObject, or nullptr if the type is not registered.
     */
    std::shared_ptr<GameObject> createObject(const std::string& objectType) const {
        auto it = creationFunctions.find(objectType);
        if (it != creationFunctions.end() && it->second) {
            return it->second();
        } else {
            return nullptr;
        }
    }

    template <typename T>
    void registerComponent(const std::string& componentType, T&& creationFunction) {
        static_assert(std::is_invocable_r_v<std::shared_ptr<Component>, T>, 
                      "creationFunction must return std::shared_ptr<Component>");
        componentFunctions.emplace(componentType, std::forward<T>(creationFunction));
        logger.log(LogLevel::INFO, "Registered component type: " + componentType);
    }

    /**
     * @brief Create a new Component of the specified type.
     *
     * @param componentType The type identifier for the Component to create.
     * @return A shared pointer to the created Component, or nullptr if the type is not registered.
     */
    std::shared_ptr<Component> createComponent(const std::string& componentType) const {
        auto it = componentFunctions.find(componentType);
        return (it != componentFunctions.end()) ? it->second() : nullptr;
    }

private:
    // A map of object type identifiers to their corresponding creation functions.
    std::map<std::string, std::function<std::shared_ptr<GameObject>()>> creationFunctions;
     std::map<std::string, std::function<std::shared_ptr<Component>()>> componentFunctions;
};
}
#endif
