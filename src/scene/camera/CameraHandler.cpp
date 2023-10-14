#include "scene/camera/CameraHandler.h"
#include "Logger.h"
#include "Engine.h"

#include <GL/glew.h>

CameraHandler::CameraHandler(glm::vec3 position, glm::vec3 target) {
	this->camera = new Camera(position, target);

	Engine* engine = Engine::getInstance();

	engine->getEventHandler()->addListener(new Listener<KeyPressEvent>([=](KeyPressEvent* event) {
		if (event->getKey() == GLFW_KEY_ESCAPE && event->getAction() == GLFW_PRESS && !engine->getConsoleHandler()->isShown()) {
			setMoving(!isMoving());
		}
	}));

	engine->getEventHandler()->addListener(new Listener<MousePositionEvent>([=](MousePositionEvent* event) {
		Engine* engine = Engine::getInstance();

		if (!this->moving) return;
		if (engine->getConsoleHandler()->isShown()) return;

		float deltaX = event->getNewPosition().x - event->getOldPosition().x;
		float deltaY = event->getNewPosition().y - event->getOldPosition().y;

		if (deltaX != 0 || deltaY != 0) {
			this->camera->setPitch(this->camera->getPitch() + -deltaY * this->sensitivity / 10);
			this->camera->setYaw(this->camera->getYaw() + deltaX * this->sensitivity / 10);
			this->camera->setTarget(this->camera->getYaw(), this->camera->getPitch());
		}
	}));

	engine->getEventHandler()->addListener(new Listener<MouseScrollEvent>([=](MouseScrollEvent* event) {
		if (!this->moving) return;
		if (engine->getConsoleHandler()->isShown()) return;

		this->fov -= event->getOffset().y;
		if (this->fov < 1.0f) this->fov = 1.0f;
		if (this->fov > 120.0f) this->fov = 120.0f;
		this->calculateProjectionMatrix();
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
	Engine* engine = Engine::getInstance();

	if (!this->moving) return;
	if (engine->getConsoleHandler()->isShown()) return;


	EventHandler* eventHandler = engine->getEventHandler();
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

	this->camera->setPosition(this->camera->getPosition() + movement * static_cast<float>(deltaTime) * this->speed);
	this->camera->calculateViewMatrix();
}

bool CameraHandler::isMoving() const {
	return this->moving;
}

void CameraHandler::setMoving(bool moving) {
	this->moving = moving;

	Engine* engine = Engine::getInstance();
	engine->getScene()->getWindowHandler()->setCursorEnabled(!moving);
}

void CameraHandler::setSensitivity(float sensitivity) {
	this->sensitivity = sensitivity;
}

float CameraHandler::getSensitivity() const {
	return this->sensitivity;
}

void CameraHandler::setSpeed(float speed) {
	this->speed = speed;
}

float CameraHandler::getSpeed() const {
	return this->speed;
}