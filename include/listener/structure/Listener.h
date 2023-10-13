#pragma once
#include "Event.h"
#include <typeindex>

class ListenerBase {
    public:
        virtual ~ListenerBase() = default;
        virtual void notify(Event* event) = 0;
        virtual std::type_index getEventType() const = 0;
};

template<typename EventType>
class Listener : public ListenerBase {
    private:
        std::function<void(EventType*)> callback;

    public:
        explicit Listener(std::function<void(EventType*)> callback) : callback(std::move(callback)) {}

        void notify(Event* event) override {
            if (EventType* typedEvent = dynamic_cast<EventType*>(event)) {
                callback(typedEvent);
            }
        }

        std::type_index getEventType() const override {
            return std::type_index(typeid(EventType));
        }
};