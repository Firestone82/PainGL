#include "scene/RenderableEntity.h"

#include <utility>
#include <stdexcept>
#include <cmath>

RenderableEntity::RenderableEntity(const std::string& name) {
    this->name = name;
}

RenderableEntity::RenderableEntity(const std::string& name, Model* model, Program* shaderProgram) {
    this->name = name;
    this->model = model;
    this->shaderProgram = shaderProgram;
}

RenderableEntity::~RenderableEntity() {
    delete this->model;
    delete this->shaderProgram;
}

std::string RenderableEntity::getName() const {
    return this->name;
}

Model* RenderableEntity::getModel() const {
    return this->model;
}

Program* RenderableEntity::getShaderProgram() const {
    return this->shaderProgram;
}

Transformation* RenderableEntity::getTransformation() {
    return &this->transformation;
}

void RenderableEntity::calculateTransformationMatrix() {
    matrix = transformation.resultMatrix();
}

glm::mat4 RenderableEntity::getTransformationMatrix() {
    return this->matrix;
}

glm::vec3 RenderableEntity::getPosition() {
    glm::mat4 mat = getTransformationMatrix();

    return {
        mat[3][0],
        mat[3][1],
        mat[3][2]
    };
}

glm::vec3 RenderableEntity::getRotation() {
    glm::mat4 mat = getTransformationMatrix();

    return {
        glm::degrees(static_cast<float>(atan2(mat[2][1], mat[2][2]))),
        glm::degrees(static_cast<float>(atan2(mat[2][0], sqrt(pow(mat[2][1], 2) + pow(mat[2][2], 2))))),
        glm::degrees(static_cast<float>(atan2(mat[1][0], mat[0][0])))
    };
}

glm::vec3 RenderableEntity::getScale() {
    glm::mat4 mat = getTransformationMatrix();

    return {
        static_cast<float>(sqrt(pow(mat[0][0], 2) + pow(mat[0][1], 2) + pow(mat[0][2], 2))),
        static_cast<float>(sqrt(pow(mat[1][0], 2) + pow(mat[1][1], 2) + pow(mat[1][2], 2))),
        static_cast<float>(sqrt(pow(mat[2][0], 2) + pow(mat[2][1], 2) + pow(mat[2][2], 2)))
    };
}

void RenderableEntity::simulate(double deltaTime) {
    if (this->simulateFunction != nullptr) {
        this->simulateFunction(this, deltaTime);
    }
}

void RenderableEntity::draw(glm::mat4 viewMatrix, glm::mat4 projectionMatrix) {
    this->shaderProgram->use();
    this->shaderProgram->setShaderVariableMatrix(this->matrix, "modelMatrix");
    this->shaderProgram->setShaderVariableMatrix(viewMatrix, "viewMatrix");
    this->shaderProgram->setShaderVariableMatrix(projectionMatrix, "projectionMatrix");
    this->model->getVAO()->bind();

    if (this->model->hasIndices()) {
        this->model->getEBO()->bind();
        glDrawElements(GL_TRIANGLES, this->model->getSize(), GL_UNSIGNED_INT, nullptr);
    } else {
        glDrawArrays(GL_TRIANGLES, 0, this->model->getSize());
    }
}

// -- Builder --

RenderableEntity::Builder::Builder(const std::string& name) {
    this->renderableEntity = new RenderableEntity(name);
}

RenderableEntity::Builder* RenderableEntity::Builder::setModel(Model* entityModel) {
    this->renderableEntity->model = entityModel;
    return this;
}

RenderableEntity::Builder* RenderableEntity::Builder::setShaderProgram(Program* programShader) {
    this->renderableEntity->shaderProgram = programShader;
    return this;
}

RenderableEntity::Builder* RenderableEntity::Builder::setTransformation(Transform::Composite* composite) {
    this->renderableEntity->transformation.setTransformation(composite);
    return this;
}

RenderableEntity::Builder* RenderableEntity::Builder::setSimulateFunction(std::function<void(RenderableEntity*, float)> callback) {
    this->renderableEntity->simulateFunction = std::move(callback);
    return this;
}

RenderableEntity* RenderableEntity::Builder::build() {
    if (this->renderableEntity->model == nullptr) {
        throw std::runtime_error("Model is required");
    }

    if (this->renderableEntity->shaderProgram == nullptr) {
        throw std::runtime_error("Shader program is required");
    }

    return this->renderableEntity;
}

RenderableEntity::Builder* RenderableEntity::createEntity(const std::string& name) {
    return new RenderableEntity::Builder(name);
}
