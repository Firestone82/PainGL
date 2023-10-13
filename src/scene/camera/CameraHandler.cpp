#include "CameraHandler.h"
#include "../../logger/Logger.h"
#include "../../engine/Engine.h"

#include <GL/glew.h>

CameraHandler::CameraHandler(glm::vec3 position, glm::vec3 target) {
	this->camera = new Camera(position, target);

	Engine* engine = Engine::getInstance();
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

void CameraHandler::update(double deltaTime) {
	EventHandler* eventHandler = Engine::getInstance()->getEventHandler();
	if (!(eventHandler->getInput()->isKeyPressed(GLFW_KEY_W)
		|| eventHandler->getInput()->isKeyPressed(GLFW_KEY_A)
        || eventHandler->getInput()->isKeyPressed(GLFW_KEY_S)
		|| eventHandler->getInput()->isKeyPressed(GLFW_KEY_D)
		|| eventHandler->getInput()->isKeyPressed(GLFW_KEY_SPACE)
		|| eventHandler->getInput()->isKeyPressed(GLFW_KEY_LEFT_SHIFT)))
		return;

	glm::vec3 direction = glm::normalize(glm::vec3(this->camera->getTarget().x,0.0f, this->camera->getTarget().z ));
	glm::vec3 right = glm::normalize(glm::cross(direction, {0.0f, 1.0f, 0.0f}));
	glm::vec3 up = glm::normalize(glm::cross(right, direction));

	glm::vec3 movement = glm::vec3(0.0f, 0.0f, 0.0f);
	if (eventHandler->getInput()->isKeyPressed(GLFW_KEY_W)) movement += direction;
	if (eventHandler->getInput()->isKeyPressed(GLFW_KEY_A)) movement -= right;
	if (eventHandler->getInput()->isKeyPressed(GLFW_KEY_S)) movement -= direction;
	if (eventHandler->getInput()->isKeyPressed(GLFW_KEY_D)) movement += right;

	if (eventHandler->getInput()->isKeyPressed(GLFW_KEY_SPACE)) movement += up;
	if (eventHandler->getInput()->isKeyPressed(GLFW_KEY_LEFT_SHIFT)) movement -= up;

	this->camera->setPosition(this->camera->getPosition() + movement * static_cast<float>(deltaTime) * 5.0f);
	this->camera->calculateViewMatrix();
}