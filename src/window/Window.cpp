#include "Engine.h"
#include "window/Window.h"
#include "utils/Logger.h"

Window::Window(int width, int height, const std::string &title) : width(width), height(height), title(title) {
	this->window = glfwCreateWindow(width, height, title.c_str(), nullptr, nullptr);
	if (!this->window) {
		Logger::error(" - Window creation failed!");
		Engine::getInstance()->stop();
		exit(EXIT_FAILURE);
	} else {
		Logger::info( " - Window created successfully!");
	}

	glfwMakeContextCurrent(this->window);

	glewExperimental = true;
	if (glewInit() != GLEW_OK) {
		Logger::error(" - GLEW initialization failed!");
		Engine::getInstance()->stop();
		exit(EXIT_FAILURE);
	} else {
		Logger::info(" - Glew initialized successfully!");
	}
}

Window::~Window() {
	glfwDestroyWindow(this->window);
	this->window = nullptr;
}

void Window::setWidth(int width) {
	this->width = width;
	glViewport(0, 0, width, this->height);
}

int Window::getWidth() const {
	return this->width;
}

void Window::setHeight(int height) {
	this->height = height;
	glViewport(0, 0, this->width, height);
}

int Window::getHeight() const {
	return this->height;
}

bool Window::shouldClose() const {
	return glfwWindowShouldClose(this->window);
}

void Window::swapBuffers() {
	glfwSwapBuffers(this->window);
}

void Window::setTitle(const std::string &title) {
	this->title = title;
	glfwSetWindowTitle(this->window, title.c_str());
}

std::string Window::getTitle() {
	return this->title;
}