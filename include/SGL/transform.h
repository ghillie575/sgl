#include <nlohmann/json.hpp>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <SGL/window.h>
#ifndef TRANSFORM_H
#define TRANSFORM_H
namespace SGL {
/**
 * @brief A class representing a 3D transformation, including position, rotation, and scaling.
 */
class Transform {
public:
    /**
     * @brief Default constructor initializing position, rotation, and scaling.
     */
    Transform() : position(0.0f), rotation(0.0f), scaling(1.0f) {}

    glm::vec3 position = glm::vec3(0, 0, 0); ///< The position of the transform.
    glm::vec3 rotation = glm::vec3(0, 0, 0); ///< The rotation of the transform (in degrees).
    glm::vec3 scaling = glm::vec3(1, 1, 1);  ///< The scaling of the transform.

    /**
     * @brief Set the position of the transform.
     * @param position The new position.
     */
    void setPosition(const glm::vec3 &position);

    /**
     * @brief Set the rotation of the transform.
     * @param rotation The new rotation (in degrees).
     */
    void setRotation(const glm::vec3 &rotation);

    /**
     * @brief Set the scaling of the transform.
     * @param scaling The new scaling.
     */
    void setScaling(const glm::vec3 &scaling);

    /**
     * @brief Get the current position of the transform.
     * @return The position as a glm::vec3.
     */
    glm::vec3 getPosition() const;

    /**
     * @brief Get the current rotation of the transform.
     * @return The rotation as a glm::vec3 (in degrees).
     */
    glm::vec3 getRotation() const;

    /**
     * @brief Get the current scaling of the transform.
     * @return The scaling as a glm::vec3.
     */
    glm::vec3 getScaling() const;

    /**
     * @brief Translate the transform by a given vector.
     * @param translation The translation vector.
     */
    void translate(const glm::vec3 &translation);

    /**
     * @brief Rotate the transform by a given vector.
     * @param rotation The rotation vector (in degrees).
     */
    void rotate(const glm::vec3 &rotation);

    /**
     * @brief Scale the transform by a given vector.
     * @param scale The scaling vector.
     */
    void scale(const glm::vec3 &scale);

    /**
     * @brief Get the transformation matrix representing the position, rotation, and scaling.
     * @return The transformation matrix as a glm::mat4.
     */
    glm::mat4 getTransformationMatrix() const;

    /**
     * @brief Serialize the transform to a JSON object.
     * @return The JSON representation of the transform.
     */
    nlohmann::json toJson() const;

    /**
     * @brief Deserialize the transform from a JSON object.
     * @param json The JSON object containing the transform data.
     */
    void fromJson(const nlohmann::json &json);
};
}
#endif