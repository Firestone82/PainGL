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

        int getWidth() const;
        int getHeight() const;
        const char* getTitle();
        GLFWwindow* get();
};
