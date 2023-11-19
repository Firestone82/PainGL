#pragma once

#include "scene/entity/EntityHandler.h"
#include "scene/light/LightHandler.h"
#include "scene/camera/CameraHandler.h"
#include "scene/sky/Sky.h"

class Scene : public Object, public Simulable<Scene> {
	private:
		EntityHandler* entityHandler;
		LightHandler* lightHandler;
		CameraHandler* cameraHandler;
		Sky* sky;

		bool showBezierCurves = false;

		explicit Scene(const std::string &name);

	public:
		~Scene();

		EntityHandler* getEntityHandler() const;
		LightHandler* getLightHandler() const;
		CameraHandler* getCameraHandler() const;

		void render();
		void simulate(float delta);

		std::vector<ShaderProgram*> getShaders() const;

		int getObjectIDAt(int posX, int posY) const;
		Object* getObjectAt(int posX, int posY) const;

		void setShowBezierCurves(bool showBezierCurves);
		bool isShowBezierCurves() const;

		class Builder {
			private:
				Scene* scene;

                glm::vec3 cameraPosition = {4.0f, 5.0f, 6.0f};
                glm::vec3 cameraTarget = {0.0f, 0.0f, 0.0f};

			public:
				explicit Builder(const std::string &name);

				Builder& addEntity(Entity* entity);
				Builder& addLight(AbstractLight* light);
				Builder& setCameraPosition(const glm::vec3 &position);
				Builder& setCameraTarget(const glm::vec3 &rotation);
				Builder& setSimulateFunction(const std::function<void(Scene*, float)> &simulateFunction);
				Builder& setSky(Sky* sky);

				Scene* build();
		};

		static Builder createScene(const std::string &name);
};