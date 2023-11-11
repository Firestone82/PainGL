#pragma once

#include "scene/light/AbstractLight.h"
#include "builder/AbstractBuilder.h"

class DirLight : public AbstractLight {
	private:
		glm::vec3 direction = glm::vec3(0.0f, 0.0f, 0.0f);

		explicit DirLight(const std::string &name);
		~DirLight() = default;

	public:
		void setDirection(const glm::vec3 direction);
		glm::vec3 getDirection();

		std::map<std::string, std::variant<glm::vec3, float>> getShaderVariables() const;

		class Builder : public AbstractBuilder<DirLight> {
			public:
				Builder(const std::string &name);

				Builder& setColor(const glm::vec3 color);
				Builder& setAmbient(const glm::vec3 ambient);
				Builder& setDiffuse(const glm::vec3 diffuse);
				Builder& setSpecular(const glm::vec3 specular);
				Builder& setDirection(const glm::vec3 direction);

				DirLight* build() override;
		};

		static Builder createLight(const std::string &name);
};