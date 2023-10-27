#pragma once

#include "scene/Scene.h"

class SceneHandler {
	private:
		std::vector<Scene*> scenes;
		Scene* currentScene;

	public:
		SceneHandler();
		~SceneHandler();

		void addScene(Scene* scene);
		void removeScene(Scene* scene);
		std::vector<Scene*> getScenes() const;

		void setActiveScene(Scene* scene);
		Scene* getActiveScene() const;
};