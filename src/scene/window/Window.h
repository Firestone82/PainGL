#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <fstream>

class Window {
    private:
        int width;
        int height;
        const char* title;
        GLFWwindow* window;

    public:
        Window(int width, int height, const char* title);
        ~Window();

        void setWidth(int width);
        int getWidth() const;

        void setHeight(int height);
        int getHeight() const;

		bool shouldClose() const;
		void swapBuffers();

        const char* getTitle();
        GLFWwindow* get();
};
