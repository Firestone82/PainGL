#include "scene/WindowHandler.h"
#include "listener/EventHandler.h"
#include "Logger.h"

#include <glm/vec2.hpp>

WindowHandler::WindowHandler(int width, int height, const char *title) {
    this->width = width;
    this->height = height;
    this->title = title;

    this->window = glfwCreateWindow(this->width, this->height, this->title, nullptr, nullptr);
    if (!this->window) {
        glfwTerminate();
        exit(EXIT_FAILURE);
    }

	glfwSetKeyCallback(window, [](GLFWwindow* window, int key, int scancode, int action, int mods) {
		EventHandler::callEvent(new KeyPressEvent(key, scancode, action, mods));
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

	glfwSetScrollCallback(window, [](GLFWwindow* window, double xoffset, double yoffset) {
		EventHandler::callEvent(new MouseScrollEvent(glm::vec2(xoffset, yoffset)));
	});

	static glm::vec2 lastMousePosition = glm::vec2(0.0f, 0.0f);
	glfwSetCursorPosCallback(window, [](GLFWwindow* window, double xpos, double ypos) {
		EventHandler::callEvent(new MousePositionEvent(lastMousePosition, glm::vec2(xpos, ypos)));
		lastMousePosition = glm::vec2(xpos, ypos);
	});

	static glm::vec2 lastWindowSize = glm::vec2(0.0f, 0.0f);
	glfwSetWindowSizeCallback(window, [](GLFWwindow* window, int width, int height) {
		EventHandler::callEvent(new WindowResizeEvent(lastWindowSize, glm::vec2(width, height)));
		lastWindowSize = glm::vec2(width, height);
	});

    glfwMakeContextCurrent(this->window);
}

WindowHandler::~WindowHandler() {
    glfwDestroyWindow(this->window);
    this->window = nullptr;
}

void WindowHandler::setWidth(int width) {
    this->width = width;
}

int WindowHandler::getWidth() const {
    return this->width;
}

void WindowHandler::setHeight(int height) {
    this->height = height;
}

int WindowHandler::getHeight() const {
    return this->height;
}

bool WindowHandler::shouldClose() const {
	return glfwWindowShouldClose(this->window);
}

void WindowHandler::swapBuffers() {
	glfwSwapBuffers(this->window);
}

void WindowHandler::setCursorEnabled(bool enabled) {
	this->cursorEnabled = enabled;
	glfwSetInputMode(this->window, GLFW_CURSOR, enabled ? GLFW_CURSOR_NORMAL : GLFW_CURSOR_DISABLED);
}

bool WindowHandler::isCursorEnabled() const {
	return this->cursorEnabled;
}

void WindowHandler::setCursorLocation(double x, double y) {
	glfwSetCursorPos(this->window, x, y);
}

const char *WindowHandler::getTitle() {
    return this->title;
}

GLFWwindow *WindowHandler::getWindow() {
    return this->window;
}
