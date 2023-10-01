#include "EventHandler.h"

std::vector<Listener *> EventHandler::listeners;

EventHandler::EventHandler(GLFWwindow *window) {
    glfwSetErrorCallback(handleError);
    glfwSetKeyCallback(window, handleKeyEvent);
    glfwSetWindowFocusCallback(window, handleWindowFocusEvent);
    glfwSetWindowIconifyCallback(window, handleWindowIconifyEvent);
    glfwSetWindowCloseCallback(window, handleWindowCloseEvent);
    glfwSetWindowSizeCallback(window, handleWindowSizeEvent);
    glfwSetCursorPosCallback(window, handleMousePositionEvent);
    glfwSetMouseButtonCallback(window, handleMouseButtonEvent);
}

void EventHandler::handleError(int error, const char *description) {
    std::cout << "Error: " << error << " - " << description << std::endl;
}

void EventHandler::addListener(Listener *listener) {
    listeners.push_back(listener);
}