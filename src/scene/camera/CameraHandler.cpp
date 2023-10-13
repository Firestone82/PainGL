#include "CameraHandler.h"
#include "../../logger/Logger.h"
#include "../../engine/Engine.h"

#include <GL/glew.h>

CameraHandler::CameraHandler(glm::vec3 position, glm::vec3 target) {
	this->camera = new Camera(position, target);

	Engine* engine = Engine::getInstance();
	engine->getEventHandler()->addListener(new Listener<KeyPressEvent>([=](KeyPressEvent* event) {
		if (event->getKey() == GLFW_KEY_W) {
			this->camera->setPosition(this->camera->getPosition() + glm::vec3(0.0f, 0.0f, 10 * engine->getDeltaTime()));
		} else if (event->getKey() == GLFW_KEY_S) {
			this->camera->setPosition(this->camera->getPosition() + glm::vec3(0.0f, 0.0f, -10 * engine->getDeltaTime()));
		} else if (event->getKey() == GLFW_KEY_A) {
			this->camera->setPosition(this->camera->getPosition() + glm::vec3(-10 * engine->getDeltaTime(), 0.0f, 0.0f));
		} else if (event->getKey() == GLFW_KEY_D) {
			this->camera->setPosition(this->camera->getPosition() + glm::vec3(10 * engine->getDeltaTime(), 0.0f, 0.0f));
		}

		camera->calculateViewMatrix();
	}));

	engine->getEventHandler()->addListener(new Listener<MousePositionEvent>([=](MousePositionEvent* event) {
		if (engine->getScene()->getWindowHandler()->isCursorEnabled()) return;

		float deltaX = event->getNewPosition().x - event->getOldPosition().x;
		float deltaY = event->getNewPosition().y - event->getOldPosition().y;

		if (deltaX != 0 || deltaY != 0) {
			this->camera->setPitch(this->camera->getPitch() + -deltaY * 0.1f);
			this->camera->setYaw(this->camera->getYaw() + deltaX * 0.1f);

			this->camera->setTarget(this->camera->getYaw(), this->camera->getPitch());
		}
	}));
}

CameraHandler::~CameraHandler() {
	delete this->camera;
}

void CameraHandler::setFov(float fov) {
	this->fov = fov;
}

float CameraHandler::getFov() const {
	return this->fov;
}

void CameraHandler::setAspectRatio(float width, float height) {
	this->aspectRatio = width / height;
	glViewport(0, 0, static_cast<int>(width), static_cast<int>(height));
}

float CameraHandler::getAspectRatio() const {
	return this->aspectRatio;
}

void CameraHandler::setNearFarPlane(glm::vec2 nearFarPlane) {
	this->nearFarPane = nearFarPlane;
}

glm::vec2 CameraHandler::getNearFarPlane() const {
	return this->nearFarPane;
}

void CameraHandler::calculateProjectionMatrix() {
	this->projectionMatrix = glm::perspective(
			glm::radians(this->fov),
			this->aspectRatio,
			this->nearFarPane[0], this->nearFarPane[1]
	);
}

glm::mat4 CameraHandler::getProjectionMatrix() {
	return this->projectionMatrix;
}

Camera* CameraHandler::getCamera() {
	return this->camera;
}

void CameraHandler::update() {

}