#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <vector>
#include <functional>
#include <iostream>
#include <map>

#include "structure/EventType.h"
#include "structure/Listener.h"
#include "structure/Event.h"

#include "event/KeyboardEvents.h"
#include "event/MouseEvents.h"
#include "event/WindowEvents.h"

#include "input/Input.h"

class EventHandler {
    private:
        static std::vector<ListenerBase*> listeners;
		Input* input;

    public:
        EventHandler();
        ~EventHandler();

        template<typename EventType>
        void addListener(Listener<EventType>* listener) {
            listeners.push_back(listener);
        }

        static void callEvent(Event* event) {
            for (auto& listener : listeners) {
                if (listener->getEventType() == std::type_index(typeid(*event))) {
                    listener->notify(event);
                }
            }

            delete event;
        }

		Input* getInput();
};