#include "scene/light/LightHandler.h"

LightHandler::~LightHandler() {
	for (const auto &light: this->lights) {
		delete light;
	}
}

void LightHandler::addLight(Light* light) {
	light->setID(this->lights.size());
	this->lights.push_back(light);
}

void LightHandler::removeLight(Light* light) {
	this->lights.erase(std::remove(this->lights.begin(), this->lights.end(), light), this->lights.end());

	// Reorder IDs of lights
	for (int i = 0; i < this->lights.size(); i++) {
		this->lights[i]->setID(i);
	}
}

const std::vector<Light*>& LightHandler::getLights() const {
	return this->lights;
}