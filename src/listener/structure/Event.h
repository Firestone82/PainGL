#pragma once
#include "EventType.h"

class Event {
    private:
        EventType type;

    public:
        explicit Event(EventType type) : type(type) {}
        virtual ~Event() = default;

        EventType getType() const {
            return type;
        }
};