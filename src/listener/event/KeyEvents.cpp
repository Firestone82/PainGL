#include "KeyEvents.h"

void EventHandler::handleKeyEvent(GLFWwindow* window, int key, int scancode, int action, int mods) {
    for (auto listener : listeners) {
        if (listener->getType() == KEY_EVENT) {
            auto* keyListener = dynamic_cast<KeyListener*>(listener);

            if (keyListener != nullptr) {
                keyListener->handle(window, key, scancode, action, mods);
            }
        }
    }
}