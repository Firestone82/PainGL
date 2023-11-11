#pragma once

#include <glm/glm.hpp>
#include "texture/Texture.h"

class Material {
	private:
		Texture* diffuseTexture = nullptr;
		glm::vec3 diffuseColor = glm::vec3(1.0f, 1.0f, 1.0f);

		Texture* specularTexture = nullptr;
		glm::vec3 specularColor = glm::vec3(1.0f, 1.0f, 1.0f);

		float shininess = 32.0f;
		float textureScale = 1.0f;

	public:
		~Material();

		void setDiffuseTexture(Texture* texture);
		Texture* getDiffuseTexture() const;

		void setDiffuseColor(glm::vec3 color);
		glm::vec3 getDiffuseColor() const;

		void setSpecularTexture(Texture* texture);
		Texture* getSpecularTexture() const;

		void setSpecularColor(glm::vec3 color);
		glm::vec3 getSpecularColor() const;

		void setShininess(float shininess);
		float getShininess() const;

		void setTextureScale(float scale);
		float getTextureScale() const;

		class Builder {
			private:
				Material* material;

			public:
				Builder();

				Builder& setDiffuseTexture(Texture* texture);
				Builder& setDiffuseTexture(const std::string &textureName);
				Builder& setDiffuseColor(glm::vec3 color);

				Builder& setSpecularTexture(Texture* texture);
				Builder& setSpecularTexture(const std::string &textureName);
				Builder& setSpecularColor(glm::vec3 color);

				Builder& setTextureScale(float scale);
				Builder& setShininess(float shininess);

				Material* build();
		};

		static Builder createMaterial();
};