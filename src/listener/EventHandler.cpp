#include "EventHandler.h"
#include "../logger/Logger.h"

std::vector<ListenerBase*> EventHandler::listeners;

EventHandler::EventHandler() {
	this->input = new Input();

	// Handle GLFW errors
    glfwSetErrorCallback([](int error, const char* description) {
        Logger::error("GLFW Error: " + std::to_string(error) + " - " + std::string(description));
    });

	// Handle keyboard input
	this->addListener(new Listener<KeyPressEvent>([=](KeyPressEvent* event) {
		this->input->setKeyState(event->getKey(), event->getAction(), event->getMods());
	}));

	// Handle mouse input
	this->addListener(new Listener<MouseButtonEvent>([=](MouseButtonEvent* event) {
		this->input->setMouseButtonState(event->getButton(), event->getAction(), event->getMods());
	}));
}

EventHandler::~EventHandler() {
	delete this->input;

    for (auto& listener : listeners) {
        delete listener;
    }

    listeners.clear();
}

Input* EventHandler::getInput() {
	return this->input;
}