#pragma once

#define GLEW_STATIC
#include <GL/glew.h>
#include "Image.h"

#include <string>
#include <vector>

enum TextureType {
	UNSPECIFIED,
	DIFFUSE,
	SPECULAR,
};

class Texture {
	private:
		std::string name;

		GLenum glType;
		TextureType type;
		GLuint texture = 0;

	public:
		Texture(const std::string &name, TextureType type, Image* image);
		~Texture();

		void bind(int slot = 0);
		void unbind();

		std::string getName() const;

		GLenum getGLType() const;
		TextureType getTextureType() const;
		std::string getTextureTypeString() const;
};