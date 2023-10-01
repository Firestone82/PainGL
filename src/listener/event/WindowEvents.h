#pragma once

#include "../EventHandler.h"

class WindowFocusListener : public Listener {
private:
    std::function<void(GLFWwindow *, int)> callback;

public:
    explicit WindowFocusListener(std::function<void(GLFWwindow *, int)> callback) : Listener(WINDOW_FOCUS_EVENT), callback(std::move(callback)) {};

    ~WindowFocusListener() override = default;

    void handle(GLFWwindow *window, int focused) {
        callback(window, focused);
    }
};

class WindowIconifyListener : public Listener {
private:
    std::function<void(GLFWwindow *, int)> callback;

public:
    explicit WindowIconifyListener(std::function<void(GLFWwindow *, int)> callback) : Listener(WINDOW_ICONIFY_EVENT), callback(std::move(callback)) {};

    ~WindowIconifyListener() override = default;

    void handle(GLFWwindow *window, int iconified) {
        callback(window, iconified);
    }
};

class WindowCloseListener : public Listener {
private:
    std::function<void(GLFWwindow *)> callback;

public:
    explicit WindowCloseListener(std::function<void(GLFWwindow *)> callback) : Listener(WINDOW_CLOSE_EVENT), callback(std::move(callback)) {};

    ~WindowCloseListener() override = default;

    void handle(GLFWwindow *window) {
        callback(window);
    }
};

class WindowSizeListener : public Listener {
private:
    std::function<void(GLFWwindow *, int, int)> callback;

public:
    explicit WindowSizeListener(std::function<void(GLFWwindow *, int, int)> callback) : Listener(WINDOW_RESIZE_EVENT), callback(std::move(callback)) {};

    ~WindowSizeListener() override = default;

    void handle(GLFWwindow *window, int width, int height) {
        callback(window, width, height);
    }
};