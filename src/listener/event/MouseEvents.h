#pragma once

#include "../structure/Event.h"
#include "../structure/EventType.h"

class MousePositionEvent : public Event {
    private:
        double x;
        double y;

    public:
        MousePositionEvent(double x, double y) : Event(EventType::MOUSE_POSITION), x(x), y(y) {}

        double getX() const {
            return x;
        }

        double getY() const {
            return y;
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