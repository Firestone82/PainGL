#pragma once
#include "../EventHandler.h"

class MousePositionListener : public Listener {
    private:
        std::function<void(GLFWwindow*, double, double)> callback;

    public:
        explicit MousePositionListener(std::function<void(GLFWwindow*, double, double)> callback) : Listener(MOUSE_POSITION_EVENT), callback(std::move(callback)) {};
        ~MousePositionListener() override = default;

        void handle(GLFWwindow* window, double xpos, double ypos) {
            callback(window, xpos, ypos);
        }
};

class MouseButtonListener : public Listener {
    private:
        std::function<void(GLFWwindow*, int, int, int)> callback;

    public:
        explicit MouseButtonListener(std::function<void(GLFWwindow*, int, int, int)> callback) : Listener(MOUSE_BUTTON_EVENT), callback(std::move(callback)) {};
        ~MouseButtonListener() override = default;

        void handle(GLFWwindow* window, int button, int action, int mods) {
            callback(window, button, action, mods);
        }
};