#pragma once

#include "../structure/Event.h"
#include "../structure/EventType.h"

#include <GL/glew.h>
#include <glm/vec2.hpp>

class MousePositionEvent : public Event {
    private:
        glm::vec2 oldPosition;
		glm::vec2 newPosition;

    public:
        MousePositionEvent(glm::vec2 oldPosition, glm::vec2 newPosition) : Event(EventType::MOUSE_POSITION), oldPosition(oldPosition), newPosition(newPosition) {}

        glm::vec2 getOldPosition() const {
			return oldPosition;
		}

		glm::vec2 getNewPosition() const {
			return newPosition;
		}
};

class MouseButtonEvent : public Event {
    private:
        int button;
        int action;
        int mods;

    public:
        MouseButtonEvent(int button, int action, int mods) : Event(EventType::MOUSE_BUTTON), button(button), action(action), mods(mods) {}

        int getButton() const {
            return button;
        }

        int getAction() const {
            return action;
        }

        int getMods() const {
            return mods;
        }
};