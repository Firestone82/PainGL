#pragma once

#include <glm/glm.hpp>
#include "texture/Texture.h"

class Material {
	private:
		std::vector<Texture*> overrideTextures;

		glm::vec3 diffuseColor = glm::vec3(1.0f, 1.0f, 1.0f);
		glm::vec3 specularColor = glm::vec3(1.0f, 1.0f, 1.0f);

		float textureScale = 1.0f;
		float shininess = 32.0f;

	public:
		void setDiffuseColor(glm::vec3 color);
		glm::vec3 getDiffuseColor() const;

		void setSpecularColor(glm::vec3 color);
		glm::vec3 getSpecularColor() const;

		void setShininess(float shininess);
		float getShininess() const;

		void setTextureScale(float scale);
		float getTextureScale() const;

		void addTexture(const std::string &texture, TextureType type);
		void addTexture(Texture* texture);
		std::vector<Texture*> getTextures() const;

		class Builder {
			private:
				Material* material;

			public:
				Builder();

				Builder& setDiffuseColor(glm::vec3 color);
				Builder& setSpecularColor(glm::vec3 color);
				Builder& setTextureScale(float scale);
				Builder& setShininess(float shininess);
				Builder& addTexture(const std::string &texture, TextureType type);

				Material* build();
		};

		static Builder createMaterial();
};