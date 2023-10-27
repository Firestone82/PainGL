#pragma once

#include "texture/Texture.h"

#include <vector>
#include <string>

class TextureHandler {
	private:
		std::string path;
		std::vector<Texture*> textures;

	public:
		TextureHandler(const std::string path, bool preLoad = false);
		~TextureHandler();

		void loadTextureFolder(const std::string &folderPath);
		Texture* loadTextureFile(const std::string &name, const std::string &path);

		std::vector<Texture*> getTextures() const;
		Texture* getTexture(const std::string &name);
};