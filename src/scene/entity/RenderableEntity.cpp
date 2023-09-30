#include "RenderableEntity.h"

RenderableEntity::RenderableEntity(Model *model, Program *shaderProgram) {
    this->model = model;
    this->shaderProgram = shaderProgram;
}

RenderableEntity::~RenderableEntity() {
    delete this->model;
    delete this->shaderProgram;
}

Model *RenderableEntity::getModel() const {
    return this->model;
}

Program *RenderableEntity::getShaderProgram() const {
    return this->shaderProgram;
}

void RenderableEntity::draw(glm::mat4 modelViewProjection) {
    this->shaderProgram->use();
    this->shaderProgram->setShaderVariableMatrix(modelViewProjection, "mvp");
    this->model->getVAO()->bind();
    glDrawArrays(GL_TRIANGLES, 0, this->model->getVertexCount());
}

glm::vec3 RenderableEntity::getPosition() const {
    return this->positionVector;
}

void RenderableEntity::setPosition(float x, float y, float z) {
    this->positionVector = glm::vec3(x, y, z);
}

glm::vec3 RenderableEntity::getRotation() const {
    return this->rotationVector;
}

void RenderableEntity::setRotation(float x, float y, float z) {
    this->rotationVector = glm::vec3(x, y, z);
}

glm::vec3 RenderableEntity::getScale() const {
    return this->scaleVector;
}

void RenderableEntity::setScale(float x, float y, float z) {
    this->scaleVector = glm::vec3(x, y, z);
}

glm::mat4 RenderableEntity::getTransformationMatrix() const {
    glm::mat4 modelMatrix = glm::mat4(1.0f);

    // Set position
    modelMatrix = glm::translate(modelMatrix, positionVector);

    // Rotate model
    modelMatrix = glm::rotate(modelMatrix, glm::radians(rotationVector.x), glm::vec3(1.0f, 0.0f, 0.0f));
    modelMatrix = glm::rotate(modelMatrix, glm::radians(rotationVector.y), glm::vec3(0.0f, 1.0f, 0.0f));
    modelMatrix = glm::rotate(modelMatrix, glm::radians(rotationVector.z), glm::vec3(0.0f, 0.0f, 1.0f));

    // Scale model
    modelMatrix = glm::scale(modelMatrix, scaleVector);

    return modelMatrix;
}
