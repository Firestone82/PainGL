#include "EventHandler.h"
#include "../logger/Logger.h"

std::vector<ListenerBase*> EventHandler::listeners;

EventHandler::EventHandler() {
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