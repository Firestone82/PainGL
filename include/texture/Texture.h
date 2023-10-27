#pragma once

#define GLEW_STATIC
#include <GL/glew.h>
#include <string>
#include <vector>

class Texture {
	private:
		std::string name;

		GLenum type;
		GLuint texture;

	public:
		Texture(const std::string &name, GLenum type);
		~Texture();

		void setData(std::vector<unsigned char> data, int width, int height);
		void bind();

		std::string getName() const;
};