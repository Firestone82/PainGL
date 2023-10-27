#pragma once

#include "window/Window.h"

#include "glm/glm.hpp"
#include <string>

class WindowHandler : public Window {
	private:
		glm::vec2 cursorLocation{};
		bool cursorEnabled = true;

	public:
		WindowHandler(int width, int height, const std::string &title);

		void setCursorEnabled(bool enabled);
		bool isCursorEnabled() const;

		void setCursorLocation(double x, double y);
		void updateCursorLocation(double x, double y);
		glm::vec2 getCursorLocation() const;
};
