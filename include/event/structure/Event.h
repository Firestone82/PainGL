#pragma once

enum class EventType {
	KEY_PRESS,
	MOUSE_POSITION,
	MOUSE_BUTTON,
	MOUSE_SCROLL,
	WINDOW_FOCUS,
	WINDOW_ICONIFY,
	WINDOW_CLOSE,
	WINDOW_RESIZE,
	CAMERA_MOVE,
	CAMERA_ROTATE,
	CAMERA_ZOOM,
	SCENE_SWITCH,
	LIGHT_UPDATE,
};

class Event {
	protected:
		EventType type;

	public:
		explicit Event(EventType type) : type(type) {}
		virtual ~Event() = default;

		EventType getType() const {
			return type;
		}
};