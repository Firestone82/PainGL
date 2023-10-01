#include "WindowEvents.h"

void EventHandler::handleWindowFocusEvent(GLFWwindow *window, int focused) {
    for (auto listener: listeners) {
        if (listener->getType() == WINDOW_FOCUS_EVENT) {
            auto *windowFocusListener = dynamic_cast<WindowFocusListener *>(listener);

            if (windowFocusListener != nullptr) {
                windowFocusListener->handle(window, focused);
            }
        }
    }
}

void EventHandler::handleWindowCloseEvent(GLFWwindow *window) {
    for (auto listener: listeners) {
        if (listener->getType() == WINDOW_CLOSE_EVENT) {
            auto *windowCloseListener = dynamic_cast<WindowCloseListener *>(listener);

            if (windowCloseListener != nullptr) {
                windowCloseListener->handle(window);
            }
        }
    }
}

void EventHandler::handleWindowIconifyEvent(GLFWwindow *window, int iconified) {
    for (auto listener: listeners) {
        if (listener->getType() == WINDOW_ICONIFY_EVENT) {
            auto *windowIconifyListener = dynamic_cast<WindowIconifyListener *>(listener);

            if (windowIconifyListener != nullptr) {
                windowIconifyListener->handle(window, iconified);
            }
        }
    }
}

void EventHandler::handleWindowSizeEvent(GLFWwindow *window, int width, int height) {
    for (auto listener: listeners) {
        if (listener->getType() == WINDOW_RESIZE_EVENT) {
            auto *windowSizeListener = dynamic_cast<WindowSizeListener *>(listener);

            if (windowSizeListener != nullptr) {
                windowSizeListener->handle(window, width, height);
            }
        }
    }
}