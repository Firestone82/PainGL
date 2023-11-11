#include "texture/Texture.h"
#include "utils/Logger.h"

Texture::Texture(const std::string &name, TextureType type, Image *image) : glType(GL_TEXTURE_2D), name(name), type(type) {
	this->texture = 0;
	glGenTextures(1, &this->texture);
	glBindTexture(this->glType, this->texture);

	glTexImage2D(this->glType, 0,
	             image->getFormat(), image->getWidth(), image->getHeight(),
	             0, image->getFormat(), GL_UNSIGNED_BYTE, image->getData());
	glGenerateMipmap(this->glType);

	// Free image data
	delete image;

	// Set texture wrapping and filtering options
	glTexParameteri(this->glType, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(this->glType, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(this->glType, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(this->glType, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	GLenum error = glGetError();
	if (error != GL_NO_ERROR) {
		Logger::error("Failed to create texture \"%s\" (%d)", name.c_str(), error);
		exit(1);
	}
}

Texture::~Texture() {
	glDeleteTextures(1, &this->texture);
	this->texture = 0;
}

void Texture::bind(int slot) {
	glActiveTexture(GL_TEXTURE0 + slot);
	glBindTexture(this->glType, this->texture);
}

void Texture::unbind() {
	glBindTexture(this->glType, 0);
}

std::string Texture::getName() const {
	return this->name;
}

GLenum Texture::getGLType() const {
	return this->glType;
}

TextureType Texture::getTextureType() const {
	return this->type;
}

std::string Texture::getTextureTypeString() const {
	switch (this->type) {
		case TextureType::DIFFUSE:
			return "DIFFUSE";

		case TextureType::SPECULAR:
			return "SPECULAR";

		default:
			return "UNSPECIFIED";
	}
}