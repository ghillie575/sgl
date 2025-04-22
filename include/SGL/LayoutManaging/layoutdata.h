#ifndef LAYOUTDATA_H
#define LAYOUTDATA_H

#include <vector>
#include <algorithm>
#include <SGL/LayoutManaging/layoutobject.h> // For std::remove

namespace SGL::LayoutManaging {

/**
 * @brief The LayoutData class manages a collection of LayoutObject pointers.
 * 
 * This class provides functionality to add, remove, and retrieve layout objects,
 * as well as query the total number of objects being managed.
 */
class LayoutData {
public:
    /**
     * @brief Constructs an empty LayoutData object.
     */
    LayoutData();

    /**
     * @brief Destroys the LayoutData object and cleans up resources.
     */
    ~LayoutData();

    /**
     * @brief Adds a LayoutObject to the collection.
     * 
     * @param object Pointer to the LayoutObject to be added.
     */
    void addObject(LayoutObject* object);

    /**
     * @brief Removes a LayoutObject from the collection.
     * 
     * @param object Pointer to the LayoutObject to be removed.
     */
    void removeObject(LayoutObject* object);

    /**
     * @brief Retrieves a LayoutObject at the specified index.
     * 
     * @param index The index of the LayoutObject to retrieve.
     * @return Pointer to the LayoutObject at the specified index.
     */
    LayoutObject* getObject(int index);

    /**
     * @brief Gets the total number of LayoutObjects in the collection.
     * 
     * @return The number of LayoutObjects currently managed.
     */
    int getObjectCount() const;

private:
    std::vector<LayoutObject*> objects_; ///< Collection of LayoutObject pointers.
};

} // namespace SGL::LayoutManaging

#endif // LAYOUTDATA_H