#include <SGL/SceneManaging/sceneobject.h>
#include <vector>

#ifndef SCENEDATA_H
#define SCENEDATA_H

namespace SGL {

/**
 * @brief The SceneData class manages a collection of SceneObject instances.
 * 
 * This class provides functionality to add, remove, and retrieve scene objects,
 * as well as to query the total number of objects in the scene.
 */
class SceneData {
public:
    /**
     * @brief Constructs a new SceneData object.
     */
    SceneData();

    /**
     * @brief Destroys the SceneData object and cleans up resources.
     */
    ~SceneData();

    /**
     * @brief Adds a SceneObject to the collection.
     * 
     * @param object Pointer to the SceneObject to be added.
     */
    void addObject(SceneObject* object);

    /**
     * @brief Removes a SceneObject from the collection.
     * 
     * @param object Pointer to the SceneObject to be removed.
     */
    void removeObject(SceneObject* object);

    /**
     * @brief Retrieves a SceneObject at the specified index.
     * 
     * @param index The index of the SceneObject to retrieve.
     * @return Pointer to the SceneObject at the specified index.
     */
    SceneObject* getObject(int index);

    /**
     * @brief Gets the total number of SceneObjects in the collection.
     * 
     * @return The number of SceneObjects.
     */
    int getObjectCount();

private:
    /**
     * @brief A collection of pointers to SceneObject instances.
     */
    std::vector<SceneObject*> objects_;
};

} // namespace SGL

#endif // SCENEDATA_H