#pragma once

#include "Texture.h"
#include "utils/FileUtils.hpp"

#include <vector>
#include <string>

class TextureHandler {
	private:
		Path folderPath;
		std::vector<Texture*> textures;

	public:
		TextureHandler(const Path &path, bool preLoad = false);
		~TextureHandler();

		void loadTextureFolder(const Path &folderPath);
		Texture* loadTextureFile(const Path &filePath, TextureType type);

		std::vector<Texture*> getTextures() const;
		Texture* getTexture(const std::string &name);

		Path getFolderPath() const;
};