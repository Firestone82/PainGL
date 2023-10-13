#include "scene/camera/Camera.h"
#include "Logger.h"

#include <glm/glm.hpp>

Camera::Camera(glm::vec3 position, glm::vec3 target) {
	setPosition(position);
	setTarget(target);
}

void Camera::setPitch(float pitch) {
	this->pitch = glm::clamp(pitch, -89.99f, 89.99f);
}

float Camera::getPitch() const {
	return this->pitch;
}

void Camera::setYaw(float yaw) {
	this->yaw = fmodf(yaw, 360.0f);
}

float Camera::getYaw() const {
	return this->yaw;
}

void Camera::calculateViewMatrix() {
	viewMatrix = glm::lookAt(
			this->position,
			this->position + this->target,
			{0.0f, 1.0f, 0.0f}
	);
}

glm::mat4 Camera::getViewMatrix() {
	return this->viewMatrix;
}

void Camera::setPosition(glm::vec3 position) {
	this->position = position;
}

glm::vec3 Camera::getPosition() const {
	return this->position;
}

void Camera::setTarget(float yaw, float pitch) {
	this->target = glm::vec3(
		cos(glm::radians(pitch)) * cos(glm::radians(yaw)),
		sin(glm::radians(pitch)),
		cos(glm::radians(pitch)) * sin(glm::radians(yaw))
	);

	calculateViewMatrix();
}

void Camera::setTarget(glm::vec3 target) {
	glm::vec3 direction = glm::normalize(target - this->position);

	this->setPitch(glm::degrees(asinf(direction.y)));
	this->setYaw(glm::degrees(atan2f(direction.z, direction.x)));
	this->setTarget(this->yaw, this->pitch);
}

glm::vec3 Camera::getTarget() const {
	return this->target;
}