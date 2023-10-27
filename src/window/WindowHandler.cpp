#include "Engine.h"
#include "window/WindowHandler.h"
#include "event/type/WindowEvents.h"
#include "event/type/KeyBoardEvents.h"
#include "event/type/MouseEvents.h"
#include "3rdparty/imgui/backend/imgui_impl_glfw.h"
#include "3rdparty/imgui/backend/imgui_impl_opengl3.h"
#include "utils/Logger.h"

WindowHandler::WindowHandler(int width, int height, const std::string &title) : Window(width, height, title) {
	this->cursorLocation = glm::vec2(width / 2, height / 2);
	setCursorLocation(int(width / 2), int(height / 2));

	// Listener for resizing the window
	Engine::getInstance()->getEventHandler()->addListener(new Listener<WindowResizeEvent>([=](WindowResizeEvent* event) {
		this->setWidth(int(event->getNewSize()[0]));
		this->setHeight(int(event->getNewSize()[1]));
	}));

	glfwSetKeyCallback(this->window, [](GLFWwindow* window, int key, int scancode, int action, int mods) {
		EventHandler::callEvent(new KeyPressEvent(key, scancode, action, mods));
	});

	glfwSetMouseButtonCallback(this->window, [](GLFWwindow* window, int button, int action, int mods) {
		EventHandler::callEvent(new MouseButtonEvent(button, action, mods));
	});

	glfwSetWindowFocusCallback(this->window, [](GLFWwindow* window, int focused) {
		EventHandler::callEvent(new WindowFocusEvent(focused));
	});

	glfwSetWindowIconifyCallback(this->window, [](GLFWwindow* window, int iconified) {
		EventHandler::callEvent(new WindowIconifyEvent(iconified));
	});

	glfwSetWindowCloseCallback(this->window, [](GLFWwindow* window) {
		EventHandler::callEvent(new WindowCloseEvent());
	});

	glfwSetScrollCallback(this->window, [](GLFWwindow* window, double xoffset, double yoffset) {
		EventHandler::callEvent(new MouseScrollEvent(glm::vec2(xoffset, yoffset)));
	});

	static glm::vec2 lastMousePosition = glm::vec2(0.0f, 0.0f);
	glfwSetCursorPosCallback(this->window, [](GLFWwindow* window, double xpos, double ypos) {
		EventHandler::callEvent(new MousePositionEvent(lastMousePosition, glm::vec2(xpos, ypos)));
		lastMousePosition = glm::vec2(xpos, ypos);
	});

	static glm::vec2 lastWindowSize = glm::vec2(0.0f, 0.0f);
	glfwSetWindowSizeCallback(this->window, [](GLFWwindow* window, int width, int height) {
		EventHandler::callEvent(new WindowResizeEvent(lastWindowSize, glm::vec2(width, height)));
		lastWindowSize = glm::vec2(width, height);
	});

	/* -- IMGUI -- */

	IMGUI_CHECKVERSION();
	ImGui::CreateContext();

	// Setup Platform/Renderer backends
	ImGui_ImplGlfw_InitForOpenGL(this->window, true);
	ImGui_ImplOpenGL3_Init();

	if (ImGui::GetCurrentContext() == nullptr) {
		Logger::error(" - ImGui initialization failed!");
		Engine::getInstance()->stop();
		exit(EXIT_FAILURE);
	} else {
		Logger::info(" - ImGui initialized successfully!");
	}
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

void WindowHandler::updateCursorLocation(double x, double y) {
	this->cursorLocation = glm::vec2(x, y);
}

glm::vec2 WindowHandler::getCursorLocation() const {
	return this->cursorLocation;
}
