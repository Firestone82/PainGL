#include "Engine.h"
#include "scene/camera/CameraHandler.h"
#include "event/type/KeyBoardEvents.h"
#include "event/type/MouseEvents.h"
#include "event/type/CameraEvents.h"
#include "event/type/WindowEvents.h"
#include "utils/Logger.h"

CameraHandler::CameraHandler(Scene* parent, glm::vec3 position, glm::vec3 target) : parentScene(parent) {
	this->camera = new Camera(position, target);

	// Listener for resizing the window
	Engine::getInstance()->getEventHandler()->addListener(new Listener<WindowResizeEvent>([=](WindowResizeEvent* event) {
		this->setAspectRatio(int(event->getNewSize()[0]), int(event->getNewSize()[1]));
		this->calculateProjectionMatrix();
		EventHandler::callEvent(new CameraZoomEvent(this));
	}));

	// Listener for toggling the camera movement on ESC key press
	Engine::getInstance()->getEventHandler()->addListener(new Listener<KeyPressEvent>([=](KeyPressEvent* event) {
		if (Engine::getInstance()->getConsoleHandler()->isEnabled()) return;

		Scene* activeScene = Engine::getInstance()->getSceneHandler()->getActiveScene();
		if (this->parentScene != activeScene) return;

		CameraHandler* cameraHandler = activeScene->getCameraHandler();
		if (event->getKey() == GLFW_KEY_ESCAPE && event->getAction() == GLFW_PRESS) {
			cameraHandler->setMoving(!cameraHandler->isMoving());
		}
	}));

	// Listener for mouse movement
	Engine::getInstance()->getEventHandler()->addListener(new Listener<MousePositionEvent>([=](MousePositionEvent* event) {
		if (Engine::getInstance()->getConsoleHandler()->isEnabled()) return;

		Scene* activeScene = Engine::getInstance()->getSceneHandler()->getActiveScene();
		CameraHandler* cameraHandler = activeScene->getCameraHandler();
		Camera* camera = cameraHandler->getCamera();

		if (this->parentScene != activeScene) return;

		float deltaX = event->getNewPosition().x - event->getOldPosition().x;
		float deltaY = event->getNewPosition().y - event->getOldPosition().y;

		if (cameraHandler->isMoving() && (deltaX != 0 || deltaY != 0)) {
			camera->setPitch(camera->getPitch() + -deltaY * cameraHandler->getSensitivity() / 10);
			camera->setYaw(camera->getYaw() + deltaX * cameraHandler->getSensitivity() / 10);
			camera->setTarget(camera->getYaw(), camera->getPitch());

			EventHandler::callEvent(new CameraRotateEvent(camera));
		}
	}));

	// Listener for mouse scroll
	Engine::getInstance()->getEventHandler()->addListener(new Listener<MouseScrollEvent>([=](MouseScrollEvent* event) {
		if (Engine::getInstance()->getConsoleHandler()->isEnabled()) return;

		Scene* scene = Engine::getInstance()->getSceneHandler()->getActiveScene();
		CameraHandler* cameraHandler = scene->getCameraHandler();

		float newFov = cameraHandler->getFov() - event->getOffset().y;
		newFov = std::min(std::max(newFov, 1.0f), 120.0f);

		if (cameraHandler->isMoving()) {
			cameraHandler->setFov(newFov);
			cameraHandler->calculateProjectionMatrix();

			EventHandler::callEvent(new CameraZoomEvent(cameraHandler));
		}
	}));

	this->setAspectRatio(Engine::getInstance()->getWindowHandler()->getWidth(), Engine::getInstance()->getWindowHandler()->getHeight());
	this->calculateProjectionMatrix();
	this->camera->calculateViewMatrix();
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

void CameraHandler::setAspectRatio(int width, int height) {
	float newRation = float(width) / float(height);

	if (newRation > 0) {
		this->aspectRatio = newRation;
	}
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
	this->projectionMatrix = glm::perspective(glm::radians(this->fov), this->aspectRatio, this->nearFarPane.x, this->nearFarPane.y);
}

glm::mat4 CameraHandler::getProjectionMatrix() {
	return this->projectionMatrix;
}

Camera* CameraHandler::getCamera() {
	return this->camera;
}

void CameraHandler::update(double deltaTime) {
	if (Engine::getInstance()->getConsoleHandler()->isEnabled()) return;
	if (!this->moving) return;

	EventHandler* eventHandler = Engine::getInstance()->getEventHandler();
	if (!(eventHandler->getInputController()->isKeyPressed(GLFW_KEY_W)
	      || eventHandler->getInputController()->isKeyPressed(GLFW_KEY_A)
	      || eventHandler->getInputController()->isKeyPressed(GLFW_KEY_S)
	      || eventHandler->getInputController()->isKeyPressed(GLFW_KEY_D)
	      || eventHandler->getInputController()->isKeyPressed(GLFW_KEY_SPACE)
	      || eventHandler->getInputController()->isKeyPressed(GLFW_KEY_LEFT_SHIFT)))
		return;

	glm::vec3 direction = glm::normalize(glm::vec3(this->camera->getTarget().x,0.0f, this->camera->getTarget().z));
	glm::vec3 right = glm::normalize(glm::cross(direction, {0.0f, 1.0f, 0.0f}));
	glm::vec3 up = glm::normalize(glm::cross(right, direction));

	glm::vec3 movement = glm::vec3(0.0f, 0.0f, 0.0f);
	if (eventHandler->getInputController()->isKeyPressed(GLFW_KEY_W)) movement += direction;
	if (eventHandler->getInputController()->isKeyPressed(GLFW_KEY_A)) movement -= right;
	if (eventHandler->getInputController()->isKeyPressed(GLFW_KEY_S)) movement -= direction;
	if (eventHandler->getInputController()->isKeyPressed(GLFW_KEY_D)) movement += right;
	if (eventHandler->getInputController()->isKeyPressed(GLFW_KEY_SPACE)) movement += up;
	if (eventHandler->getInputController()->isKeyPressed(GLFW_KEY_LEFT_SHIFT)) movement -= up;

	this->camera->setPosition(this->camera->getPosition() + movement * float(deltaTime) * this->speed);
	this->camera->calculateViewMatrix();

	EventHandler::callEvent(new CameraMoveEvent(this->getCamera()));
}

bool CameraHandler::isMoving() const {
	return this->moving;
}

void CameraHandler::setMoving(bool moving) {
	this->moving = moving;
	Engine::getInstance()->getWindowHandler()->setCursorEnabled(!moving);
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
