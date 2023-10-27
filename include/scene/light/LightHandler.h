#pragma once

#include "scene/light/Light.h"

class LightHandler {
	private:
		std::vector<Light*> lights;

	public:
		~LightHandler();

		void addLight(Light* light);
		void removeLight(Light* light);

		const std::vector<Light*>& getLights() const;
};