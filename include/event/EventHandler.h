#pragma once

#include <vector>
#include <typeindex>
#include "event/structure/Listener.h"
#include "event/InputController.h"

class EventHandler {
	private:
		static std::vector<ListenerBase*> listeners;
		InputController* inputController;

	public:
		EventHandler();
		~EventHandler();

		template<typename EventType>
		void addListener(Listener<EventType>* listener) {
			listeners.push_back(listener);
		}

		static void callEvent(Event* event) {
			for (const auto& listener: listeners) {
				if (listener->getEventType() == std::type_index(typeid(*event))) {
					listener->notify(event);
				}
			}

			delete event;
		}

		InputController* getInputController();
};