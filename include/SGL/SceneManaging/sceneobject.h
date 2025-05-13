#include <nlohmann/json.hpp>
#include <SGL/transform.h>
#include <SGL/object.h>
#include <SGL/component.h>
#include <SGL/physics/phys_propreties.h>

#ifndef SCENE_OBJECT_H
#define SCENE_OBJECT_H

namespace SGL {

/**
 * @brief Represents an object in the scene with various properties such as transform, model, shader, etc.
 */
class SceneObject {
public:
    Transform transform; ///< Transformation properties of the scene object (position, rotation, scale).
    std::string model; ///< Path to the model file associated with the scene object.
    std::string shader; ///< Shader program used for rendering the object.
    std::string id; ///< Unique identifier for the scene object.
    std::string name = "x"; ///< Name of the scene object (default is "x").
    std::string type = "default"; ///< Type of the scene object (default is "default").
    std::string texture = "blank.jpg"; ///< Path to the texture file (default is "blank.jpg").
    Material material = Material(); ///< Material properties of the object (e.g., color, shininess).
    PhysProperties properties; ///< Physical properties of the object (e.g., mass, friction).
    std::vector<std::string> components; ///< List of components attached to the scene object.
    std::vector<VertexAttribute> vertexAttributes; ///< List of vertex attributes for the object.

    /**
     * @brief Default constructor for SceneObject.
     */
    SceneObject();

    /**
     * @brief Adds a component to the scene object.
     * @param type The type of the component to add.
     */
    void addComponent(std::string type);
    void addVertexAttribute(int size, int location);
    /**
     * @brief Parses JSON data to initialize the scene object.
     * @param json The JSON object containing the scene object data.
     */
    void fromJson(const nlohmann::json& json);

    /**
     * @brief Sets the name of the scene object.
     * @param name The new name for the scene object.
     */
    void setObjectName(std::string name);

    /**
     * @brief Converts the scene object to a JSON representation.
     * @return A JSON object representing the scene object.
     */
    nlohmann::json toJson() const;

private:
    /**
     * @brief Generates a random unique identifier for the scene object.
     * @param length The length of the generated ID.
     * @return A randomly generated ID string.
     */
    std::string generateRandomID(int length);
};

} // namespace SGL

#endif