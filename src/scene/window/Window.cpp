#include "Window.h"

Window::Window(int width, int height, const char *title) {
    this->width = width;
    this->height = height;
    this->title = title;

    this->window = glfwCreateWindow(this->width, this->height, this->title, nullptr, nullptr);
    if (!this->window) {
        glfwTerminate();
        exit(EXIT_FAILURE);
    }

    glfwMakeContextCurrent(this->window);
    glfwSwapInterval(1);

    glViewport(0, 0, width, height);
}

Window::~Window() {
    glfwDestroyWindow(this->window);
    this->window = nullptr;
}

void Window::setWidth(int width) {
    this->width = width;
}

int Window::getWidth() const {
    return this->width;
}

void Window::setHeight(int height) {
    this->height = height;
}

int Window::getHeight() const {
    return this->height;
}

const char *Window::getTitle() {
    return this->title;
}

GLFWwindow *Window::get() {
    return this->window;
}
