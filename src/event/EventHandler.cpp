#include "event/EventHandler.h"
#include "utils/Logger.h"

#include <GL/glew.h>
#include <GLFW/glfw3.h>

std::vector<ListenerBase*> EventHandler::listeners;

EventHandler::EventHandler() {
	this->inputController = new InputController();

	// Handle GLFW errors
	glfwSetErrorCallback([](int error, const char* description) {
		Logger::error("GLFW Error: " + std::to_string(error) + " - " + std::string(description));
	});
}

EventHandler::~EventHandler() {
	delete this->inputController;

	for (const auto& listener: EventHandler::listeners) {
		delete listener;
	}

	EventHandler::listeners.clear();
}

InputController* EventHandler::getInputController() {
	return this->inputController;
}