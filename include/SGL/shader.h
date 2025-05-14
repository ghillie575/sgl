#include <iostream>
#include <string>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <SGL/logger.h>

#ifndef SHADER_H
#define SHADER_H

namespace SGL {

/**
 * @brief Represents a shader program in OpenGL.
 * This class provides functionality to load, compile, and use shaders,
 * as well as set uniform variables for the shader program.
 */
class Shader
{
public:
    unsigned int ID; ///< OpenGL ID of the shader program.

    /**
     * @brief Constructs a Shader object and loads/compiles shaders from file paths.
     * @param vertexPath Path to the vertex shader source file.
     * @param fragmentPath Path to the fragment shader source file.
     */
    Shader(const char *vertexPath, const char *fragmentPath);
    Shader(const char *vertexCode, const char *fragmentCode , bool rawCode);

    /**
     * @brief Default constructor for Shader.
     * Initializes an empty shader object.
     */
    Shader();

    Logger loadLogger = Logger("SHADER_L"); ///< Logger for shader loading operations.
    Logger compileLogger = Logger("SHADER_C"); ///< Logger for shader compilation operations.

    /**
     * @brief Activates the shader program for use in OpenGL.
     */
    void use() const;

    /**
     * @brief Sets a boolean uniform variable in the shader.
     * @param name Name of the uniform variable.
     * @param value Boolean value to set.
     */
    void setBool(const std::string &name, bool value) const;

    /**
     * @brief Sets an integer uniform variable in the shader.
     * @param name Name of the uniform variable.
     * @param value Integer value to set.
     */
    void setInt(const std::string &name, int value) const;

    /**
     * @brief Sets a float uniform variable in the shader.
     * @param name Name of the uniform variable.
     * @param value Float value to set.
     */
    void setFloat(const std::string &name, float value) const;

    /**
     * @brief Sets a vec2 uniform variable in the shader.
     * @param name Name of the uniform variable.
     * @param value glm::vec2 value to set.
     */
    void setVec2(const std::string &name, const glm::vec2 &value) const;

    /**
     * @brief Sets a vec2 uniform variable in the shader using individual components.
     * @param name Name of the uniform variable.
     * @param x X component of the vec2.
     * @param y Y component of the vec2.
     */
    void setVec2(const std::string &name, float x, float y) const;

    /**
     * @brief Sets a vec3 uniform variable in the shader.
     * @param name Name of the uniform variable.
     * @param value glm::vec3 value to set.
     */
    void setVec3(const std::string &name, const glm::vec3 &value) const;

    /**
     * @brief Sets a vec3 uniform variable in the shader using individual components.
     * @param name Name of the uniform variable.
     * @param x X component of the vec3.
     * @param y Y component of the vec3.
     * @param z Z component of the vec3.
     */
    void setVec3(const std::string &name, float x, float y, float z) const;

    /**
     * @brief Sets a vec4 uniform variable in the shader.
     * @param name Name of the uniform variable.
     * @param value glm::vec4 value to set.
     */
    void setVec4(const std::string &name, const glm::vec4 &value) const;

    /**
     * @brief Sets a vec4 uniform variable in the shader using individual components.
     * @param name Name of the uniform variable.
     * @param x X component of the vec4.
     * @param y Y component of the vec4.
     * @param z Z component of the vec4.
     * @param w W component of the vec4.
     */
    void setVec4(const std::string &name, float x, float y, float z, float w) const;

    /**
     * @brief Sets a mat2 uniform variable in the shader.
     * @param name Name of the uniform variable.
     * @param mat glm::mat2 value to set.
     */
    void setMat2(const std::string &name, const glm::mat2 &mat) const;

    /**
     * @brief Sets a mat3 uniform variable in the shader.
     * @param name Name of the uniform variable.
     * @param mat glm::mat3 value to set.
     */
    void setMat3(const std::string &name, const glm::mat3 &mat) const;

    /**
     * @brief Sets a mat4 uniform variable in the shader.
     * @param name Name of the uniform variable.
     * @param mat glm::mat4 value to set.
     */
    void setMat4(const std::string &name, const glm::mat4 &mat) const;

private:
    /**
     * @brief Checks for shader compilation or linking errors.
     * @param shader ID of the shader or program to check.
     * @param type Type of shader or program ("VERTEX", "FRAGMENT", "PROGRAM").
     */
    void checkCompileErrors(unsigned int shader, std::string type);
};

} // namespace SGL

#endif