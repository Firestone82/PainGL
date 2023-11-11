#include "texture/TextureHandler.h"
#include "utils/FileUtils.hpp"
#include "utils/StringUtils.h"

#include "utils/Logger.h"

TextureHandler::TextureHandler(const Path &path, bool preLoad) : folderPath(path) {
	if (preLoad) this->loadTextureFolder(path);
}

TextureHandler::~TextureHandler() {
	Logger::debug("\nDestroying %zu textures", this->textures.size());

	for (Texture* texture: this->textures) {
		std::string name = texture->getName();
		delete texture;
		Logger::debug(R"( - Texture "%s" destroyed)", name.c_str());
	}
}

void TextureHandler::loadTextureFolder(const Path &folderPath) {
	for (const auto &filePath: FileUtils::getFiles(folderPath)) {

		TextureType textureType = TextureType::UNSPECIFIED;
		if (StringUtils::endsWith(filePath.getFileNameWithoutExtension(),"_spec")) {
			textureType = TextureType::SPECULAR;
		} else if (StringUtils::endsWith(filePath.getFileNameWithoutExtension(),"_diff")) {
			textureType = TextureType::DIFFUSE;
		}

		// Skip files that are not texture of model
		if (textureType == TextureType::UNSPECIFIED) {
			continue;
		}

		loadTextureFile(filePath, textureType);
	}

	Logger::debug("");
}

Texture* TextureHandler::loadTextureFile(const Path &filePath, TextureType type) {
	Logger::debug(R"(Loading texture "%s")", filePath.toString().c_str());

	if (!filePath.exists()) {
		Logger::error(R"( - File does not exist)");
		return nullptr;
	}

	Image* image = new Image(filePath);
	if (image->getData() == nullptr) {
		Logger::error(R"( - Failed to load image)");
		return nullptr;
	}

	Texture* texture = new Texture(filePath.getFileNameWithoutExtension(), type, image);
	this->textures.push_back(texture);

	Logger::debug(" - Successfully loaded texture.");
	return texture;
}

std::vector<Texture*> TextureHandler::getTextures() const {
	return this->textures;
}

Texture* TextureHandler::getTexture(const std::string &name) {
	for (Texture* texture: this->textures) {
		if (texture->getName() == name) {
			return texture;
		}
	}

	std::optional<Path> filePath = FileUtils::findFileInFolder(this->folderPath, name);

	if (filePath.has_value()) {
		Path path = filePath.value();

		TextureType type = TextureType::UNSPECIFIED;
		if (StringUtils::endsWith("_diff", path.getFileNameWithoutExtension())) {
			type = TextureType::DIFFUSE;
		} else if (StringUtils::endsWith("_spec", path.getFileNameWithoutExtension())) {
			type = TextureType::SPECULAR;
		}

		return this->loadTextureFile(path, type);
	}

	return nullptr;
}

Path TextureHandler::getFolderPath() const {
	return this->folderPath;
}
