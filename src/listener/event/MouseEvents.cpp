#include "MouseEvents.h"

void EventHandler::handleMousePositionEvent(GLFWwindow *window, double xpos, double ypos) {
    for (auto listener : listeners) {
        if (listener->getType() == MOUSE_POSITION_EVENT) {
            auto* mousePositionListener = dynamic_cast<MousePositionListener*>(listener);

            if (mousePositionListener != nullptr) {
                mousePositionListener->handle(window, xpos, ypos);
            }
        }
    }
}

void EventHandler::handleMouseButtonEvent(GLFWwindow *window, int button, int action, int mods) {
    for (auto listener : listeners) {
        if (listener->getType() == MOUSE_BUTTON_EVENT) {
            auto* mouseButtonListener = dynamic_cast<MouseButtonListener*>(listener);

            if (mouseButtonListener != nullptr) {
                mouseButtonListener->handle(window, button, action, mods);
            }
        }
    }
}