#pragma once

#include <map>

class Input {
	private:
		std::map<int, std::tuple<int, int>> keyboardKeys;
		std::map<int, std::tuple<int, int>> mouseButtons;

	public:
		Input();

		void setKeyState(int key, int state, int mod);
		bool isKeyPressed(int key);
		bool isKeyReleased(int key);
		int getKeyMod(int key);

		void setMouseButtonState(int button, int state, int mod);
		bool isMousePressed(int button);
		bool isMouseReleased(int button);
		int getMouseMod(int button);
};