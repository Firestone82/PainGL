#include "Scene.h"

Scene::Scene(int width, int height, const char* title) {
    this->windowHandler = new WindowHandler(width, height, title);
	this->cameraHandler = new CameraHandler({2, 3, 10000000}, {0, 0, 0});
}

Scene::~Scene() {
    delete this->windowHandler;
}

void Scene::renderEntity(RenderableEntity* entity) {
    this->entities.push_back(entity);
}

void Scene::disposeEntity(RenderableEntity* entity) {
	this->entities.erase(std::remove(this->entities.begin(), this->entities.end(), entity), this->entities.end());
}

void Scene::draw() {
	for (const auto &entity: this->entities) {
        entity->calculateTransformationMatrix();
        entity->draw(
				cameraHandler->getCamera()->getViewMatrix(),
				cameraHandler->getProjectionMatrix()
		);
    }
}

void Scene::tick(double deltaTime) {
	cameraHandler->update(deltaTime);

    for (const auto &entity: this->entities) {
        entity->simulate(deltaTime);
    }
}

WindowHandler* Scene::getWindowHandler() {
    return this->windowHandler;
}

CameraHandler* Scene::getCameraHandler() {
	return this->cameraHandler;
}

const std::vector<RenderableEntity*>& Scene::getEntities() {
    return this->entities;
}