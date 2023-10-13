#include "listener/Input.h"

Input::Input() {
	this->keyboardKeys = std::map<int, std::tuple<int, int>>();
	this->mouseButtons = std::map<int, std::tuple<int, int>>();
}

void Input::setKeyState(int key, int state, int mod) {
	this->keyboardKeys[key] = std::make_tuple(state, mod);
}

bool Input::isKeyPressed(int key) {
	if (this->keyboardKeys.find(key) == this->keyboardKeys.end()) {
		return false;
	}

	return std::get<0>(this->keyboardKeys[key]) > 0;
}

bool Input::isKeyReleased(int key) {
	if (this->keyboardKeys.find(key) == this->keyboardKeys.end()) {
		return false;
	}

	return std::get<0>(this->keyboardKeys[key]) == 0;
}

int Input::getKeyMod(int key) {
	if (this->keyboardKeys.find(key) == this->keyboardKeys.end()) {
		return -1;
	}

	return std::get<1>(this->keyboardKeys[key]);
}

void Input::setMouseButtonState(int button, int state, int mod) {
	this->mouseButtons[button] = std::make_tuple(state, mod);
}

bool Input::isMousePressed(int button) {
	if (this->mouseButtons.find(button) == this->mouseButtons.end()) {
		return false;
	}

	return std::get<0>(this->mouseButtons[button]) > 0;
}

bool Input::isMouseReleased(int button) {
	if (this->mouseButtons.find(button) == this->mouseButtons.end()) {
		return false;
	}

	return std::get<0>(this->mouseButtons[button]) == 0;
}

int Input::getMouseMod(int button) {
	if (this->mouseButtons.find(button) == this->mouseButtons.end()) {
		return -1;
	}

	return std::get<1>(this->mouseButtons[button]);
}