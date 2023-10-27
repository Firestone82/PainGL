#include "scene/entity/Entity.h"
#include "utils/Logger.h"
#include "Engine.h"

Entity::~Entity() {
	this->model = nullptr;
	this->shaderProgram = nullptr;
	delete this->transformation;
}

static bool first = true;
void Entity::draw() {
    Scene* scene = Engine::getInstance()->getSceneHandler()->getActiveScene();

	this->shaderProgram->use();

	// TODO: Make entity static and dynamic
    // Model
	this->shaderProgram->setShaderVariableMatrix(this->matrix, "modelMatrix");
	this->shaderProgram->setShaderVariableMatrix(glm::transpose(glm::inverse(glm::mat3(this->matrix))), "normalMatrix");

    // Material
    this->shaderProgram->setShaderVariableVector(this->material->getAmbientColor(), "material.ambientColor");
    this->shaderProgram->setShaderVariableVector(this->material->getObjectColor(), "material.objectColor");
    this->shaderProgram->setShaderVariableFloat(this->material->getSpecular(), "material.specular");
    this->shaderProgram->setShaderVariableFloat(this->material->getShininess(), "material.shininess");
    this->shaderProgram->setShaderVariableFloat(this->material->getShininess(), "material.shininess");

	this->model->getVAO()->bind();

//	if (this->material->getTexture() != nullptr) {
//		this->material->getTexture()->bind();
//	}

	if (this->model->hasIndices()) {
		this->model->getEBO()->bind();
		glDrawElements(GL_TRIANGLES, this->model->getSize(), GL_UNSIGNED_INT, nullptr);
	} else {
		glDrawArrays(GL_TRIANGLES, 0, this->model->getSize());
	}
}

Model* Entity::getModel() const {
	return this->model;
}

ShaderProgram* Entity::getShaderProgram() const {
	return this->shaderProgram;
}

Material* Entity::getMaterial() const {
	return this->material;
}

// -- Builder --

Entity::Builder::Builder(const std::string &name) {
	this->renderableEntity = new Entity(name);
	this->renderableEntity->material = new Material();
}

Entity::Builder* Entity::Builder::setModel(Model* model) {
	this->renderableEntity->model = model;
	return this;
}

Entity::Builder* Entity::Builder::setModel(const std::string &model) {
	this->renderableEntity->model = Engine::getInstance()->getModelHandler()->getModel(model);
	return this;
}

Entity::Builder* Entity::Builder::setShaderProgram(ShaderProgram* shaderProgram) {
	this->renderableEntity->shaderProgram = shaderProgram;
	return this;
}

Entity::Builder* Entity::Builder::setShaderProgram(const std::string &vertex, const std::string &fragment) {
	this->renderableEntity->shaderProgram = Engine::getInstance()->getShaderHandler()->createProgram(fragment, vertex);
	return this;
}

Entity::Builder* Entity::Builder::setStatik(bool statik) {
	this->renderableEntity->statik = statik;
	return this;
}

Entity::Builder* Entity::Builder::setMaterial(Material* material) {
	this->renderableEntity->material = material;
	return this;
}

Entity::Builder* Entity::Builder::setTransformation(Transform::Composite* composite) {
	this->renderableEntity->transformation->setTransformation(composite);
	return this;
}

Entity::Builder* Entity::Builder::setSimulateFunction(const std::function<void(Entity*, float)>& simulateFunction) {
	this->renderableEntity->simulateFunction = simulateFunction;
	return this;
}

Entity* Entity::Builder::build() {
	return this->renderableEntity;
}

Entity::Builder* Entity::createEntity(const std::string &name) {
	return new Entity::Builder(name);
}