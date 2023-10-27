#include "texture/Texture.h"
#include "utils/Logger.h"

Texture::Texture(const std::string &name, GLenum type) : name(name), type(type) {
	this->texture = 0;
	glGenTextures(1, &this->texture);
	glBindTexture(type, this->texture);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
}

Texture::~Texture() {
	glDeleteTextures(1, &this->texture);
}

void Texture::setData(std::vector<unsigned char> data, int width, int height) {
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data.data());
	glGenerateMipmap(GL_TEXTURE_2D);

	// TODO: Text successfully loaded
}

void Texture::bind() {
	glBindTexture(this->type, this->texture);
}

std::string Texture::getName() const {
	return this->name;
}