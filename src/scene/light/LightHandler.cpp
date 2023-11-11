#include "event/type/LightEvents.h"
#include "scene/light/LightHandler.h"
#include "scene/light/type/SpotLight.h"
#include "scene/light/type/PointLight.h"
#include "scene/light/type/DirLight.h"
#include "scene/light/type/FlashLight.h"
#include "utils/Logger.h"
#include "Engine.h"

LightHandler::LightHandler(Scene* parent) {
	this->parentScene = parent;

	Engine::getInstance()->getEventHandler()->addListener(new Listener<LightUpdateEvent>([=](LightUpdateEvent* event) {
		AbstractLight* light = event->getLight();
		std::string id = std::to_string(light->getID());

		if (light->getID() < 0) return;

		// Ignore lights out of active scene
		Scene* activeScene = Engine::getInstance()->getSceneHandler()->getActiveScene();
		if (this->parentScene != activeScene) return;

		for (const auto& shaderProgram : activeScene->getShaders()) {
			shaderProgram->use();

			Renderable* renderable = dynamic_cast<Renderable*>(light);
			if (renderable != nullptr) {
				renderable->calculateTransformationMatrix();
                renderable->getMaterial()->setDiffuseColor(light->getDiffuse());
			}

			shaderProgram->setShaderLight(light);
		}
	}));
}

LightHandler::~LightHandler() {
	for (const auto &light: this->lights) {
		delete light;
	}
}

void LightHandler::addLight(AbstractLight* light) {
	light->setID(this->lights.size());
	this->lights.push_back(light);
}

void LightHandler::removeLight(AbstractLight* light) {
	this->lights.erase(std::remove(this->lights.begin(), this->lights.end(), light), this->lights.end());

	// Reorder IDs of lights
	for (int i = 0; i < this->lights.size(); i++) {
		this->lights[i]->setID(i);
	}
}

const std::vector<AbstractLight*>& LightHandler::getLights() const {
	return this->lights;
}