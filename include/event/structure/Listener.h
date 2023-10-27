#pragma once

#include "Event.h"

#include <typeindex>
#include <functional>

class AbstractListener {
	public:
		virtual ~AbstractListener() = default;
		virtual void notify(Event* event) = 0;
		virtual std::type_index getEventType() const = 0;
};

template<typename EventType>
class Listener : public AbstractListener {
	private:
		std::function<void(EventType*)> callback;

	public:
		explicit Listener(const std::function<void(EventType*)>& callback) : callback(callback) {}

		void notify(Event* event) override {
			if (EventType* typedEvent = dynamic_cast<EventType*>(event)) {
				callback(typedEvent);
			}
		}

		std::type_index getEventType() const override {
			return std::type_index(typeid(EventType));
		}
};