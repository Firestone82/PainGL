#include "Engine.h"
#include "event/InputController.h"
#include "event/type/KeyBoardEvents.h"
#include "event/type/MouseEvents.h"
#include "event/structure/Listener.h"

InputController::InputController() {
	this->keyboardKeys = std::map<int, std::tuple<int, int>>();
	this->mouseButtons = std::map<int, std::tuple<int, int>>();

	// Listener for keyboard input
	Engine::getInstance()->getEventHandler()->addListener(new Listener<KeyPressEvent>([=](KeyPressEvent* event) {
		setKeyState(event->getKey(), event->getAction(), event->getMods());
	}));

	// Listener for mouse input
	Engine::getInstance()->getEventHandler()->addListener(new Listener<MouseButtonEvent>([=](MouseButtonEvent* event) {
		setMouseButtonState(event->getButton(), event->getAction(), event->getMods());
	}));
}

void InputController::setKeyState(int key, int state, int mod) {
	this->keyboardKeys[key] = std::make_tuple(state, mod);
}

bool InputController::isKeyPressed(int key) {
	return std::get<0>(this->keyboardKeys[key]) > 0;
}

int InputController::getKeyMod(int key) {
	return std::get<1>(this->keyboardKeys[key]);
}

void InputController::setMouseButtonState(int button, int state, int mod) {
	this->mouseButtons[button] = std::make_tuple(state, mod);
}

bool InputController::isMouseButtonPressed(int button) {
	return std::get<0>(this->mouseButtons[button]) > 0;
}

int InputController::getMouseButtonMod(int button) {
	return std::get<1>(this->mouseButtons[button]);
}