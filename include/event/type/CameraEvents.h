#pragma once

#include "event/structure/Event.h"

class Scene;
class Camera;
class CameraHandler;

class CameraZoomEvent : public Event {
	private:
		CameraHandler* cameraHandler;

	public:
		explicit CameraZoomEvent(CameraHandler* cameraHandler)
			: Event(EventType::CAMERA_ZOOM), cameraHandler(cameraHandler) {}

		CameraHandler* getCameraHandler() const {
			return cameraHandler;
		}
};

class CameraMoveEvent : public Event {
	private:
		Camera* camera;

	public:
		explicit CameraMoveEvent(Camera* camera)
			: Event(EventType::CAMERA_MOVE), camera(camera) {}

		Camera* getCamera() const {
			return camera;
		}
};

class CameraRotateEvent : public Event {
	private:
		Camera* camera;

	public:
		explicit CameraRotateEvent(Camera* camera)
			: Event(EventType::CAMERA_ROTATE), camera(camera) {}

		Camera* getCamera() const {
			return camera;
		}
};