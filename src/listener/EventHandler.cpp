#include "EventHandler.h"
#include "../logger/Logger.h"

std::vector<ListenerBase*> EventHandler::listeners;

EventHandler::EventHandler(GLFWwindow* window) {
    glfwSetKeyCallback(window, [](GLFWwindow* window, int key, int scancode, int action, int mods) {
        EventHandler::callEvent(new KeyPressEvent(key, scancode, action, mods));
    });

    glfwSetCursorPosCallback(window, [](GLFWwindow* window, double xpos, double ypos) {
        EventHandler::callEvent(new MousePositionEvent(xpos, ypos));
    });

    glfwSetMouseButtonCallback(window, [](GLFWwindow* window, int button, int action, int mods) {
        EventHandler::callEvent(new MouseButtonEvent(button, action, mods));
    });

    glfwSetWindowFocusCallback(window, [](GLFWwindow* window, int focused) {
        EventHandler::callEvent(new WindowFocusEvent(focused));
    });

    glfwSetWindowIconifyCallback(window, [](GLFWwindow* window, int iconified) {
        EventHandler::callEvent(new WindowIconifyEvent(iconified));
    });

    glfwSetWindowCloseCallback(window, [](GLFWwindow* window) {
        EventHandler::callEvent(new WindowCloseEvent());
    });

    glfwSetWindowSizeCallback(window, [](GLFWwindow* window, int width, int height) {
        EventHandler::callEvent(new WindowResizeEvent(width, height));
    });

    glfwSetErrorCallback([](int error, const char* description) {
        Logger::error("GLFW Error: " + std::to_string(error) + " - " + std::string(description));
    });
}

EventHandler::~EventHandler() {
    for (auto& listener : listeners) {
        delete listener;
    }

    listeners.clear();
}