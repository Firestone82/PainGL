#include "scene/entity/Entity.h"
#include "utils/Logger.h"
#include "Engine.h"

// -- Builder --

Entity::Builder::Builder(const std::string &name) {
	this->entity = new Entity(name);
	this->entity->material = Material::createMaterial().build();
}

Entity::Builder& Entity::Builder::setModel(const std::string &model) {
	this->entity->model = Engine::getInstance()->getModelHandler()->getModel(model);
	return *this;
}

Entity::Builder& Entity::Builder::setShaderProgram(const std::string &vertex, const std::string &fragment) {
	this->entity->shaderProgram = Engine::getInstance()->getShaderHandler()->createProgram(vertex, fragment);
	return *this;
}

Entity::Builder& Entity::Builder::setShaderProgram(ShaderProgram* shaderProgram) {
	this->entity->shaderProgram = shaderProgram;
	return *this;
}

Entity::Builder& Entity::Builder::setMaterial(Material* material) {
	this->entity->material = material;
	return *this;
}

Entity::Builder& Entity::Builder::setTransformation(Transform::Composite* composite) {
	this->entity->transformation->setTransformation(composite);
	return *this;
}

Entity::Builder& Entity::Builder::setSimulateFunction(const std::function<void(Entity*, float)>& simulateFunction) {
	this->entity->simulateFunction = simulateFunction;
	return *this;
}

Entity::Builder& Entity::Builder::addTexture(const std::string &texture, TextureType type) {
	Texture* tex = Engine::getInstance()->getTextureHandler()->getTexture(texture);

	if (tex == nullptr) {
		Logger::warning("ModelBuilder::addTexture() | Texture \"%s\" not found", texture.c_str());
		return *this;
	}

	return *this;
}

Entity* Entity::Builder::build() {
	return this->entity;
}

Entity::Builder Entity::createEntity(const std::string &name) {
	return Entity::Builder(name);
}