#pragma once

#include "../structure/Event.h"
#include "../structure/EventType.h"

class KeyPressEvent : public Event {
    private:
        int key;
        int scancode;
        int action;
        int mods;

    public:
        KeyPressEvent(int key, int scancode, int action, int mods)
            : Event(EventType::KEY_PRESS), key(key), scancode(scancode), action(action), mods(mods) {}

        int getKey() const {
            return key;
        }

        int getScanCode() const {
            return scancode;
        }

        int getAction() const {
            return action;
        }

        int getMods() const {
            return mods;
        }
};