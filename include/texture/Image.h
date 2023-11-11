#pragma once

#include "utils/FileUtils.hpp"

#define GLEW_STATIC
#include <GL/glew.h>
#include <string>

class Image {
	private:
		Path path;

		int width;
		int height;
		int channels;
		GLenum format;

		unsigned char* data;

	public:
		Image(const Path &path);
		~Image();

		Path getPath() const;

		int getWidth() const;
		int getHeight() const;
		int getChannels() const;
		GLenum getFormat() const;

		unsigned char* getData() const;
};