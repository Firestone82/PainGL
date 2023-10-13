#pragma once

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

class Camera {
    private:
		float pitch = 0.0f;
		float yaw = 0.0f;

		glm::mat4 viewMatrix = glm::mat4(1.0f);
		glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f);
        glm::vec3 target = glm::vec3(0.0f, 0.0f, 0.0f);

    public:
		Camera(glm::vec3 position, glm::vec3 target);

		void setPitch(float pitch);
		float getPitch() const;

		void setYaw(float yaw);
		float getYaw() const;

		void calculateViewMatrix();
		glm::mat4 getViewMatrix();

		void setPosition(glm::vec3 position);
		glm::vec3 getPosition() const;

		void setTarget(float yaw, float pitch);
		void setTarget(glm::vec3 target);
		glm::vec3 getTarget() const;
};