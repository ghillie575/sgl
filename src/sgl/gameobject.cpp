#include <sgl/core/gameobject.h>
#include <sgl/utils.h>
bool back = false;
void GameObject::begin()
{
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, model->vertexCount * sizeof(float), model->vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, model->indexCount * sizeof(unsigned int), model->indices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void *)0);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void *)(3 * sizeof(float)));
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);

    glBindBuffer(GL_ARRAY_BUFFER, 0);

    glBindVertexArray(0);
}

void GameObject::render()
{
    if (useTexture)
    {
        texture->bind();
    }
    shader->use();
    // calculate matrix

    glm::mat4 trans = glm::mat4(1.0f);
    trans = glm::scale(trans, scale);
    trans = glm::rotate(trans, rot.x, glm::vec3(1.0, 0.0, 0.0));
    trans = glm::rotate(trans, rot.y, glm::vec3(0.0, 1.0, 0.0));
    trans = glm::rotate(trans, rot.z, glm::vec3(0.0, 0.0, 1.0));
    trans = glm::translate(trans, pos);

    shader->setMat4("transform", trans);
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
    
}
GameObject::GameObject(Model *model, Shader *shader) : shader(shader), model(model)
{
    useTexture = false;
}
GameObject::GameObject(Model *model, Shader *shader, Texture *texture) : shader(shader), model(model), texture(texture)
{
}
void GameObject::setRotation(glm::vec3 rotation)
{
    this->rot = rotation;
}
void GameObject::setPosition(glm::vec3 position)
{
    this->pos = position;
}
void GameObject::setScale(glm::vec3 scale)
{
    this->scale = scale;
}