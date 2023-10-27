#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <string>

class Window {
	protected:
		int width;
		int height;
		std::string title;

		GLFWwindow* window;

	public:
		Window(int width, int height, const std::string &title);
		~Window();

		void setWidth(int width);
		int getWidth() const;

		void setHeight(int height);
		int getHeight() const;

		bool shouldClose() const;
		void swapBuffers();

		void setTitle(const std::string &title);
		std::string getTitle();
};