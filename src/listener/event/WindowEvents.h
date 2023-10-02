#pragma once

#include "../structure/Event.h"
#include "../structure/EventType.h"

class WindowFocusEvent : public Event {
    private:
        bool focused;

    public:
        WindowFocusEvent(bool focused) : Event(EventType::WINDOW_FOCUS), focused(focused) {}

        bool isFocused() const {
            return focused;
        }
};

class WindowIconifyEvent : public Event {
    private:
        bool iconified;

    public:
        WindowIconifyEvent(bool iconified) : Event(EventType::WINDOW_ICONIFY), iconified(iconified) {}

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
        int width;
        int height;

    public:
        WindowResizeEvent(int width, int height) : Event(EventType::WINDOW_RESIZE), width(width), height(height) {}

        int getWidth() const {
            return width;
        }

        int getHeight() const {
            return height;
        }
};