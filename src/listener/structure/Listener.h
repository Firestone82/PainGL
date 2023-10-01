#pragma once

class Listener {
protected:
    EventType type;

public:
    explicit Listener(EventType type) : type(type) {};

    virtual ~Listener() = default;

    EventType getType() const {
        return type;
    };
};