#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <vector>
#include <functional>
#include <iostream>

#include "structure/EventType.h"
#include "structure/Listener.h"
#include "event/KeyEvents.h"
#include "event/WindowEvents.h"

class EventHandler {
    protected:
        static std::vector<Listener*> listeners;

    public:
        explicit EventHandler(GLFWwindow* window);
        ~EventHandler() = default;

        static void handleError(int error, const char* description);
        static void handleKeyEvent(GLFWwindow* window, int key, int scancode, int action, int mods);
        static void handleWindowFocusEvent(GLFWwindow* window, int focused);
        static void handleWindowIconifyEvent(GLFWwindow* window, int iconified);
        static void handleWindowCloseEvent(GLFWwindow* window);
        static void handleWindowSizeEvent(GLFWwindow* window, int width, int height);
        static void handleMousePositionEvent(GLFWwindow* window, double xpos, double ypos);
        static void handleMouseButtonEvent(GLFWwindow* window, int button, int action, int mods);

        void addListener(Listener* listener);
};