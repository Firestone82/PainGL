#pragma once

#include "Camera.h"

#include <glm/glm.hpp>
#include <glm/mat4x4.hpp>

class Scene;
class CameraHandler {
	private:
		Scene* parentScene;
		Camera* camera;

		float fov = 60.0f;
		float aspectRatio = 4.0f / 3.0f;
		glm::vec2 nearFarPane = {0.01f, 100.0f};

		bool moving = false;
		float sensitivity = 1.0f;
		float speed = 5.0f;

		glm::mat4 projectionMatrix = glm::mat4(1.0f);

	public:
		CameraHandler(Scene* parent, glm::vec3 position, glm::vec3 target);
		~CameraHandler();

		void setFov(float fov);
		float getFov() const;

		void setAspectRatio(int width, int height);
		float getAspectRatio() const;

		void setNearFarPlane(glm::vec2 nearFarPlane);
		glm::vec2 getNearFarPlane() const;

		void calculateProjectionMatrix();
		glm::mat4 getProjectionMatrix();

		Camera* getCamera();
		void update(double deltaTime);

		bool isMoving() const;
		void setMoving(bool moving);

		void setSensitivity(float sensitivity);
		float getSensitivity() const;

		void setSpeed(float speed);
		float getSpeed() const;
};
