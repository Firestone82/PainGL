#include "scene/Scene.h"
#include "utils/Logger.h"
#include "event/type/SceneEvents.h"
#include "event/EventHandler.h"

Scene::Scene(const std::string &name) : name(name) {
	this->entityHandler = new EntityHandler();
	this->lightHandler = new LightHandler();
	this->cameraHandler = new CameraHandler(this, {3.0f, 2.0f, 3.0f}, glm::vec3(0.0f));
}

Scene::~Scene() {
	delete this->entityHandler;
	delete this->lightHandler;
	delete this->cameraHandler;
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
	for (const auto &light: this->lightHandler->getLights()) {
		light->calculateTransformationMatrix();
		light->draw();
	}

	for (const auto &entity: this->entityHandler->getEntities()) {
		entity->calculateTransformationMatrix();
		entity->draw();
	}
}

void Scene::simulate(float delta) {
	this->cameraHandler->update(delta);

	for (const auto &entity: this->entityHandler->getEntities()) {
		entity->simulate(delta);
	}
}

std::string Scene::getName() const {
	return this->name;
}

void Scene::setID(int id) {
	this->id = id;
}

int Scene::getID() const {
	return this->id;
}

// -- Builder --

Scene::Builder::Builder(const std::string &name) {
	this->scene = new Scene(name);
}

Scene::Builder* Scene::Builder::addEntity(Entity* entity) {
	this->scene->entityHandler->addEntity(entity);
	return this;
}

Scene::Builder* Scene::Builder::addLight(Light* light) {
	this->scene->lightHandler->addLight(light);
	return this;
}

Scene::Builder* Scene::Builder::setCameraPosition(const glm::vec3 &position) {
	this->cameraPosition = position;
	return this;
}

Scene::Builder* Scene::Builder::setCameraTarget(const glm::vec3 &target) {
	this->cameraTarget = target;
	return this;
}

Scene* Scene::Builder::build() {
    this->scene->cameraHandler->getCamera()->setPosition(this->cameraPosition);
    this->scene->cameraHandler->getCamera()->setTarget(this->cameraTarget);
	return this->scene;
}

Scene::Builder* Scene::createScene(const std::string &name) {
	return new Builder(name);
}