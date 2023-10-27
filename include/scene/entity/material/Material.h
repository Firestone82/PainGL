#pragma once

#include "texture/Texture.h"

#include <glm/glm.hpp>

class Material {
	private:
		glm::vec3 ambientColor = glm::vec3(0.1f, 0.1f, 0.1f);
		glm::vec3 objectColor = glm::vec3(1.0f, 1.0f, 1.0f);
		float specular = 1.0f;
		float shininess = 32.0f;

		Texture* texture = nullptr;

	public:
		~Material();

		void setAmbientColor(glm::vec3 ambientColor);
		glm::vec3 getAmbientColor() const;

		void setObjectColor(glm::vec3 objectColor);
		glm::vec3 getObjectColor() const;

		void setSpecular(float specular);
		float getSpecular() const;

		void setShininess(float shininess);
		float getShininess() const;

		Texture* getTexture() const;

		class Builder {
			private:
				Material* material;

			public:
				Builder();

				Builder* setAmbientColor(glm::vec3 ambientColor);
				Builder* setObjectColor(glm::vec3 objectColor);
				Builder* setSpecular(float specular);
				Builder* setShininess(float shininess);
				Builder* setTexture(Texture* texture);

				Material* build();
		};

		static Builder* createMaterial();
};