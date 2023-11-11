#include "Engine.h"
#include "utils/Logger.h"
#include "event/type/MouseEvents.h"
#include "event/type/CameraEvents.h"
#include "event/type/KeyBoardEvents.h"
#include "event/type/SceneEvents.h"
#include "event/type/LightEvents.h"

SceneHandler::SceneHandler() {
	this->currentScene = nullptr;

	// Listener for scene switching by pressing F1-F12
	Engine::getInstance()->getEventHandler()->addListener(new Listener<KeyPressEvent>([=](KeyPressEvent* event) {
		if (Engine::getInstance()->getConsoleHandler()->isEnabled()) return;

		if (event->getKey() >= GLFW_KEY_F1 && event->getKey() <= GLFW_KEY_F12 && event->getAction() == GLFW_PRESS) {
			int sceneIndex = event->getKey() - GLFW_KEY_F1;
			if (sceneIndex >= this->scenes.size()) return;

			Scene* scene = this->scenes[sceneIndex];
			this->setActiveScene(scene);
		}
	}));

	// Listener for switching scenes by event
	Engine::getInstance()->getEventHandler()->addListener(new Listener<SceneSwitchEvent>([=](SceneSwitchEvent* event) {
		for (const auto& shaderProgram: event->getNewScene()->getShaders()) {
			shaderProgram->use();
			shaderProgram->setShaderVariable(event->getNewScene()->getCameraHandler()->getCamera()->getViewMatrix(), "viewMatrix");
			shaderProgram->setShaderVariable(event->getNewScene()->getCameraHandler()->getProjectionMatrix(), "projectionMatrix");
			shaderProgram->setShaderVariable(event->getNewScene()->getCameraHandler()->getCamera()->getPosition(), "camera.position");

			shaderProgram->setShaderVariable((int) event->getNewScene()->getLightHandler()->getLights().size(), "numLights");
			for (AbstractLight* light: event->getNewScene()->getLightHandler()->getLights()) {
                if (light->getID() < 0) continue;
				EventHandler::callEvent(new LightUpdateEvent(light));
			}
		}
	}));
}

SceneHandler::~SceneHandler() {
	Logger::debug("\nDestroying %d scenes", this->scenes.size());

	for (const auto& scene: this->scenes) {
		Logger::debug(R"( - Deleting scene: "%s")", scene->getName().c_str());
		delete scene;
	}

	this->scenes.clear();
}

void SceneHandler::addScene(Scene* scene) {
	scene->setID(this->scenes.size());

	Logger::debug(R"(Adding new scene: "%s" (#%d))", scene->getName().c_str(), scene->getID());
	this->scenes.push_back(scene);

	if (this->currentScene == nullptr) {
		Logger::debug(" - Setting scene as active scene");
		this->currentScene = scene;
	}
}

void SceneHandler::removeScene(Scene* scene) {
	this->scenes.erase(std::remove(this->scenes.begin(), this->scenes.end(), scene), this->scenes.end());

	// Reorder the IDs
	for (int i = 0; i < this->scenes.size(); i++) {
		this->scenes[i]->setID(i);
	}
}

std::vector<Scene*> SceneHandler::getScenes() const {
	return this->scenes;
}

void SceneHandler::setActiveScene(Scene* scene) {
	if (this->currentScene == scene) return;

	Scene* previousScene = this->currentScene;
	if (previousScene != nullptr) {
		this->currentScene->getCameraHandler()->setMoving(false);
	}

	Logger::debug(R"(Switching active scene to "%s")", scene->getName().c_str());
	this->currentScene = scene;

	EventHandler::callEvent(new SceneSwitchEvent(previousScene, this->currentScene));
}

Scene* SceneHandler::getActiveScene() {
	return this->currentScene;
}