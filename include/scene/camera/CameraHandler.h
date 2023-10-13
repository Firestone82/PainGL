#pragma once

#include "Camera.h"

class CameraHandler {
	private:
		Camera* camera;

		float fov = 60.0f;
		float aspectRatio = 4.0f / 3.0f;
		glm::vec2 nearFarPane = {0.01f, 100.0f};

		glm::mat4 projectionMatrix = glm::mat4(1.0f);

	public:
		CameraHandler(glm::vec3 position, glm::vec3 target);
		~CameraHandler();

		void setFov(float fov);
		float getFov() const;

		void setAspectRatio(float width, float height);
		float getAspectRatio() const;

		void setNearFarPlane(glm::vec2 nearFarPlane);
		glm::vec2 getNearFarPlane() const;

		void calculateProjectionMatrix();
		glm::mat4 getProjectionMatrix();

		Camera* getCamera();
		void update(double deltaTime);
};
