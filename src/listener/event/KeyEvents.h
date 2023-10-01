#pragma once

#include "../EventHandler.h"

class KeyListener : public Listener {
private:
    std::function<void(GLFWwindow *, int, int, int, int)> callback;

public:
    explicit KeyListener(std::function<void(GLFWwindow *, int, int, int, int)> callback) : Listener(KEY_EVENT), callback(std::move(callback)) {};

    ~KeyListener() override = default;

    void handle(GLFWwindow *window, int key, int scancode, int action, int mods) {
        callback(window, key, scancode, action, mods);
    }
};
