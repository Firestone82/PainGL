#pragma once

#include "scene/entity/EntityHandler.h"
#include "scene/light/LightHandler.h"
#include "scene/camera/CameraHandler.h"

class Scene {
	private:
		int id = -1;
		std::string name;

		EntityHandler* entityHandler;
		LightHandler* lightHandler;
		CameraHandler* cameraHandler;

		explicit Scene(const std::string &name);

	public:
		~Scene();

		EntityHandler* getEntityHandler() const;
		LightHandler* getLightHandler() const;
		CameraHandler* getCameraHandler() const;

		void render();
		void simulate(float delta);

		std::string getName() const;

		void setID(int id);
		int getID() const;

		class Builder {
			private:
				Scene* scene;

                glm::vec3 cameraPosition = {4.0f, 5.0f, 8.0f};
                glm::vec3 cameraTarget = {0.0f, 0.0f, 0.0f};

			public:
				explicit Builder(const std::string &name);

				Builder* addEntity(Entity* entity);
				Builder* addLight(Light* light);
				Builder* setCameraPosition(const glm::vec3 &position);
				Builder* setCameraTarget(const glm::vec3 &rotation);

				Scene* build();
		};

		static Builder* createScene(const std::string &name);
};