#define STB_IMAGE_IMPLEMENTATION
#include "3rdparty/stb/stb_image.h"

#include "texture/Image.h"

Image::Image( const Path &path) : path(path) {
	int nrChannels = 0;

	this->data = stbi_load(path.toString().c_str(), &width, &height, &nrChannels, 0);
	this->format = nrChannels == 1 ? GL_RED : nrChannels == 3 ? GL_RGB : GL_RGBA;
}

Image::~Image() {
	stbi_image_free(data);
	this->data = nullptr;
}

Path Image::getPath() const {
	return path;
}

int Image::getWidth() const {
	return width;
}

int Image::getHeight() const {
	return height;
}

int Image::getChannels() const {
	return channels;
}

GLenum Image::getFormat() const {
	return format;
}

GLubyte* Image::getData() const {
	return data;
}