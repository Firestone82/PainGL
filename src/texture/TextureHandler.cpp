#include "texture/TextureHandler.h"
#include "utils/FileUtils.h"
#include "utils/StringUtils.h"

#define STB_IMAGE_IMPLEMENTATION
#include "3rdparty/stb/stb_image.h"

TextureHandler::TextureHandler(const std::string path, bool preLoad) : path(path) {
	if (preLoad) {
		this->loadTextureFolder(path);
	}
}

TextureHandler::~TextureHandler() {
	Logger::debug("\nDestroying %zu textures", this->textures.size());

	for (Texture* texture : this->textures) {
		std::string name = texture->getName();
		delete texture;
		Logger::debug(R"( - Texture "%s" destroyed)", name.c_str());
	}
}

void TextureHandler::loadTextureFolder(const std::string &folderPath) {
	for (std::string file : FileUtils::getFiles(folderPath)) {
		std::vector<std::string> args = StringUtils::split(file, "\\");

		this->loadTextureFile(args[1], file);
	}
}

Texture* TextureHandler::loadTextureFile(const std::string &name, const std::string &path) {
	Logger::debug(R"(Loading texture "%s" from file "%s")", name.c_str(), path.c_str());

	Texture* texture = new Texture(name, GL_TEXTURE_2D);

	int width, height, nrChannels;
	std::vector<unsigned char> data;
	unsigned char* dataPtr = stbi_load(path.c_str(), &width, &height, &nrChannels, 0);

	if (dataPtr) {
		data = std::vector<unsigned char>(dataPtr, dataPtr + width * height * nrChannels);
		stbi_image_free(dataPtr);
	} else {
		Logger::error(R"( - Failed to load texture "%s")", name.c_str());
	}

	Logger::debug(R"( - Texture "%s" loaded: %dx%d)", name.c_str(), width, height);
	texture->setData(data, width, height);

	this->textures.push_back(texture);
	return texture;
}

std::vector<Texture*> TextureHandler::getTextures() const {
	return this->textures;
}

Texture* TextureHandler::getTexture(const std::string &name) {
	for (Texture* texture : this->textures) {
		if (texture->getName() == name) {
			return texture;
		}
	}

	return nullptr;
}

