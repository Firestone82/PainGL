#include "RenderableEntity.h"

#include <utility>
#include <stdexcept>

RenderableEntity::RenderableEntity(const std::string &name) {
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

void RenderableEntity::setPosition(float x, float y, float z) {
    this->positionVector = glm::vec3(x, y, z);
}

glm::vec3 RenderableEntity::getPosition() const {
    return this->positionVector;
}

void RenderableEntity::setRotation(float x, float y, float z) {
    this->rotationVector = glm::vec3(x, y, z);

    if (this->rotationVector.x > 360.0f) {
        this->rotationVector.x = 0.0f;
    } else if (this->rotationVector.x < 0.0f) {
        this->rotationVector.x = 360.0f;
    }

    if (this->rotationVector.y > 360.0f) {
        this->rotationVector.y = 0.0f;
    } else if (this->rotationVector.y < 0.0f) {
        this->rotationVector.y = 360.0f;
    }

    if (this->rotationVector.z > 360.0f) {
        this->rotationVector.z = 0.0f;
    } else if (this->rotationVector.z < 0.0f) {
        this->rotationVector.z = 360.0f;
    }
}

glm::vec3 RenderableEntity::getRotation() const {
    return this->rotationVector;
}

void RenderableEntity::setScale(float x, float y, float z) {
    this->scaleVector = glm::vec3(x, y, z);

    if (this->scaleVector.x < 0.0f) {
        this->scaleVector.x = 0.0f;
    }

    if (this->scaleVector.y < 0.0f) {
        this->scaleVector.y = 0.0f;
    }

    if (this->scaleVector.z < 0.0f) {
        this->scaleVector.z = 0.0f;
    }
}

void RenderableEntity::setScale(float scale) {
    this->setScale(scale, scale, scale);
}

glm::vec3 RenderableEntity::getScale() const {
    return this->scaleVector;
}

void RenderableEntity::simulate(float deltaTime) {
    if (this->simulateFunction != nullptr) {
        this->simulateFunction(this, deltaTime);
    }
}

void RenderableEntity::draw(glm::mat4 modelViewProjection) {
    this->shaderProgram->use();
    this->shaderProgram->setShaderVariableMatrix(modelViewProjection, "mvp");
    this->model->getVAO()->bind();

    if (this->model->hasIndices()) {
        this->model->getEBO()->bind();
        glDrawElements(GL_TRIANGLES, this->model->getVerticesCount(), GL_UNSIGNED_INT, nullptr);
    } else {
        glDrawArrays(GL_TRIANGLES, 0, this->model->getVerticesCount());
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

RenderableEntity::Builder* RenderableEntity::Builder::setPosition(float x, float y, float z) {
    this->renderableEntity->positionVector = glm::vec3(x, y, z);
    return this;
}

RenderableEntity::Builder* RenderableEntity::Builder::setRotation(float x, float y, float z) {
    this->renderableEntity->rotationVector = glm::vec3(x, y, z);
    return this;
}

RenderableEntity::Builder* RenderableEntity::Builder::setScale(float scale) {
    this->renderableEntity->scaleVector = glm::vec3(scale, scale, scale);
    return this;
}

RenderableEntity::Builder* RenderableEntity::Builder::setScale(float x, float y, float z) {
    this->renderableEntity->scaleVector = glm::vec3(x, y, z);
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
