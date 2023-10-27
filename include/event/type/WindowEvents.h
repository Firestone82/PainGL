#pragma once

#include "event/structure/Event.h"
#include <glm/vec2.hpp>

class WindowFocusEvent : public Event {
	private:
		bool focused;

	public:
		explicit WindowFocusEvent(bool focused)
			: Event(EventType::WINDOW_FOCUS), focused(focused) {}

		bool isFocused() const {
			return focused;
		}
};

class WindowIconifyEvent : public Event {
	private:
		bool iconified;

	public:
		explicit WindowIconifyEvent(bool iconified)
			: Event(EventType::WINDOW_ICONIFY), iconified(iconified) {}

		bool isIconified() const {
			return iconified;
		}
};

class WindowCloseEvent : public Event {
	public:
		WindowCloseEvent() : Event(EventType::WINDOW_CLOSE) {}
};

class WindowResizeEvent : public Event {
	private:
		glm::vec2 oldSize;
		glm::vec2 newSize;

	public:
		WindowResizeEvent(glm::vec2 oldSize, glm::vec2 newSize)
			: Event(EventType::WINDOW_RESIZE), oldSize(oldSize), newSize(newSize) {}

		glm::vec2 getOldSize() const {
			return oldSize;
		}

		glm::vec2 getNewSize() const {
			return newSize;
		}
};