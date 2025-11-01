#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H
#include <sgl/logger.h>
#include <sgl/core/model.h>
#include <sgl/core/shader.h>
#include <sgl/core/texture.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
class GameObject
{
public:
    void begin();
    void render();
    GameObject(Model *model, Shader *shader);
    GameObject(Model *model, Shader *shader, Texture *texture);
    void setPosition(glm::vec3 position);
    void setRotation(glm::vec3 position);
    void setScale(glm::vec3 position);
    glm::vec3 getPosition() { return pos; }
    glm::vec3 getRotation() { return rot; }
    glm::vec3 getScale() { return scale; }

private:
    glm::vec3 pos, rot, scale;
    bool useTexture;
    Model *model;
    Texture *texture;
    Shader *shader;
    unsigned int VBO, VAO, EBO;
};
#endif