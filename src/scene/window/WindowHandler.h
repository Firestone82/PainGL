#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <fstream>

class WindowHandler {
    private:
        int width;
        int height;
        const char* title;
        GLFWwindow* window;

		bool cursorEnabled = true;

    public:
        WindowHandler(int width, int height, const char* title);
        ~WindowHandler();

        void setWidth(int width);
        int getWidth() const;

        void setHeight(int height);
        int getHeight() const;

		bool shouldClose() const;
		void swapBuffers();

		void setCursorEnabled(bool enabled);
		bool isCursorEnabled() const;

		void setCursorLocation(double x, double y);

        const char* getTitle();
        GLFWwindow* getWindow();
};
