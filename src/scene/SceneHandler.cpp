#include "Engine.h"
#include "utils/Logger.h"
#include "event/type/MouseEvents.h"
#include "event/type/CameraEvents.h"
#include "event/type/KeyBoardEvents.h"
#include "event/type/SceneEvents.h"

SceneHandler::SceneHandler() {
	this->currentScene = nullptr;

	// Listener for scene switching
	Engine::getInstance()->getEventHandler()->addListener(new Listener<KeyPressEvent>([=](KeyPressEvent* event) {
		if (Engine::getInstance()->getConsoleHandler()->isEnabled()) return;

		if (event->getKey() >= GLFW_KEY_F1 && event->getKey() <= GLFW_KEY_F12 && event->getAction() == GLFW_PRESS) {
			int sceneIndex = event->getKey() - GLFW_KEY_F1;
			if (sceneIndex >= this->scenes.size()) return;

			Scene* scene = this->scenes[sceneIndex];
			this->setActiveScene(scene);
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

Scene* SceneHandler::getActiveScene() const {
	return this->currentScene;
}