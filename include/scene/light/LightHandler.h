#pragma once

#include "scene/light/AbstractLight.h"

class Scene;
class LightHandler {
	private:
		Scene* parentScene;
		std::vector<AbstractLight*> lights;

	public:
		LightHandler(Scene* parent);
		~LightHandler();

		void addLight(AbstractLight* light);
		void removeLight(AbstractLight* light);

		const std::vector<AbstractLight*>& getLights() const;
};