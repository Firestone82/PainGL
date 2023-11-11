#pragma once

#include <map>
#include <glm/vec2.hpp>

class InputController {
	private:
		std::map<int, std::tuple<int, int>> keyboardKeys;
		std::map<int, std::tuple<int, int>> mouseButtons;
		glm::vec2 mousePosition;

	public:
		InputController();

		void setKeyState(int key, int state, int mod);
		bool isKeyPressed(int key);
		int getKeyMod(int key);

		void setMouseButtonState(int button, int state, int mod);
		bool isMouseButtonPressed(int button);
		int getMouseButtonMod(int button);

		glm::vec2 getMousePosition();
};