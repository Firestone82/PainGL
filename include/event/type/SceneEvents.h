#pragma once

#include "event/structure/Event.h"
#include <glm/vec2.hpp>

class Scene;

class SceneSwitchEvent : public Event {
	private:
		Scene* oldScene;
		Scene* newScene;

	public:
		SceneSwitchEvent(Scene* oldScene, Scene* newScene)
			: Event(EventType::WINDOW_FOCUS), oldScene(oldScene), newScene(newScene) {}

		Scene* getOldScene() const {
			return oldScene;
		}

		Scene* getNewScene() const {
			return newScene;
		}
};