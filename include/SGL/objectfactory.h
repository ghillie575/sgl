#ifndef OBJECTFACTORY_H
#define OBJECTFACTORY_H
#include <map>
#include <string>
#include <memory>
#include <functional>
#include <SGL/object.h>
/**
 * @class ObjectFactory
 * @brief A factory class for creating GameObject instances.
 *
 * This class allows registering creation functions for different types of 
 * GameObjects and creating instances of those objects when needed.
 */
class ObjectFactory {
public:
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
    void registerObjectCreationFunction(const std::string& objectType, T&& creationFunction) {
        static_assert(std::is_invocable_r_v<std::shared_ptr<GameObject>, T>, 
                      "creationFunction must return std::shared_ptr<GameObject>");
        creationFunctions.emplace(objectType, std::forward<T>(creationFunction));
    }

    /**
     * @brief Create a new object of the specified type.
     *
     * @param objectType The type identifier for the object to create.
     * @return A shared pointer to the created GameObject, or nullptr if the type is not registered.
     */
    std::shared_ptr<GameObject> createObject(const std::string& objectType) const {
        auto it = creationFunctions.find(objectType);
        return (it != creationFunctions.end()) ? it->second() : nullptr;
    }

private:
    // A map of object type identifiers to their corresponding creation functions.
    std::map<std::string, std::function<std::shared_ptr<GameObject>()>> creationFunctions;
};
#endif
