#include "scene/Scene.h"
#include "utils/Logger.h"
#include "event/type/SceneEvents.h"
#include "event/EventHandler.h"
#include "Engine.h"

Scene::Scene(const std::string &name) : Object(name) {
	this->entityHandler = new EntityHandler();
	this->lightHandler = new LightHandler(this);
	this->cameraHandler = new CameraHandler(this, {3.0f, 2.0f, 3.0f}, glm::vec3(0.0f));
	this->skyBox = nullptr;
}

Scene::~Scene() {
	delete this->entityHandler;
	delete this->lightHandler;
	delete this->cameraHandler;

	if (this->skyBox != nullptr) {
		delete this->skyBox;
	}
}

EntityHandler* Scene::getEntityHandler() const {
	return this->entityHandler;
}

LightHandler* Scene::getLightHandler() const {
	return this->lightHandler;
}

CameraHandler* Scene::getCameraHandler() const {
	return this->cameraHandler;
}

void Scene::render() {
	for (const auto &entity: this->entityHandler->getEntities()) {
		glStencilFunc(GL_ALWAYS, entity->getID() + 1, 0xFF);
		entity->calculateTransformationMatrix();
		entity->draw();
	}

	int entityCount = this->entityHandler->getEntities().size();
	for (const auto &light: this->lightHandler->getLights()) {
		Renderable* renderable = dynamic_cast<Renderable*>(light);
		if (renderable == nullptr) continue;

		glStencilFunc(GL_ALWAYS, entityCount + light->getID() + 1, 0xFF);
		renderable->calculateTransformationMatrix();
		renderable->draw();
	}

	if (this->skyBox != nullptr) {
		this->skyBox->draw();
	}
}

void Scene::simulate(float delta) {
	if (this->simulateFunction != nullptr) {
		this->simulateFunction(this, delta);
	}

	this->cameraHandler->update(delta);

	for (const auto &entity: this->entityHandler->getEntities()) {
		entity->simulate(delta);
	}
}

std::vector<ShaderProgram*> Scene::getShaders() const {
	std::vector<ShaderProgram*> shaders;

	for (const auto &entity: this->entityHandler->getEntities()) {
		Renderable* renderable = dynamic_cast<Renderable*>(entity);
		if (renderable == nullptr) continue;

		ShaderProgram* shaderProgram = renderable->getShaderProgram();
		if (std::find(shaders.begin(), shaders.end(), shaderProgram) == shaders.end()) {
			shaders.push_back(shaderProgram);
		}
	}

	for (const auto &light: this->lightHandler->getLights()) {
		Renderable* renderable = dynamic_cast<Renderable*>(light);
		if (renderable == nullptr) continue;

		ShaderProgram* shaderProgram = renderable->getShaderProgram();
		if (std::find(shaders.begin(), shaders.end(), shaderProgram) == shaders.end()) {
			shaders.push_back(shaderProgram);
		}
	}

	return shaders;
}

int Scene::getObjectIDAt(int posX, int posY) const {
	int objectID = 0;
	glReadPixels(posX, posY, 1, 1, GL_STENCIL_INDEX, GL_UNSIGNED_INT, &objectID);

	if (objectID == 0) {
		return -1;
	}

	return objectID - 1;
}

Object* Scene::getObjectAt(int posX, int posY) const {
	int objectID = this->getObjectIDAt(posX, posY);
	if (objectID == -1) return nullptr;

	if (objectID < this->entityHandler->getEntities().size()) {
		return this->entityHandler->getEntities()[objectID];
	}

	if (objectID < this->entityHandler->getEntities().size() + this->lightHandler->getLights().size()) {
		return this->lightHandler->getLights()[objectID - this->entityHandler->getEntities().size()];
	}

	return nullptr;
}

// -- Builder --

Scene::Builder::Builder(const std::string &name) {
	this->scene = new Scene(name);
}

Scene::Builder& Scene::Builder::addEntity(Entity* entity) {
	this->scene->entityHandler->addEntity(entity);
	return *this;
}

Scene::Builder& Scene::Builder::addLight(AbstractLight* light) {
	this->scene->lightHandler->addLight(light);
	return *this;
}

Scene::Builder& Scene::Builder::setCameraPosition(const glm::vec3 &position) {
	this->cameraPosition = position;
	return *this;
}

Scene::Builder& Scene::Builder::setCameraTarget(const glm::vec3 &target) {
	this->cameraTarget = target;
	return *this;
}

Scene::Builder& Scene::Builder::setSimulateFunction(const std::function<void(Scene*, float)> &simulateFunction) {
	this->scene->simulateFunction = simulateFunction;
	return *this;
}

Scene::Builder& Scene::Builder::setSkyBox(const std::string &name, const std::vector<Path> &images) {
	this->scene->skyBox = new SkyBox(name, images);
	return *this;
}

Scene* Scene::Builder::build() {
    this->scene->cameraHandler->getCamera()->setPosition(this->cameraPosition);
    this->scene->cameraHandler->getCamera()->setTarget(this->cameraTarget);
	return this->scene;
}

Scene::Builder Scene::createScene(const std::string &name) {
	return Scene::Builder(name);
}