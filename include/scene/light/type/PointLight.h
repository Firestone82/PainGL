#pragma once

#include "scene/light/AbstractRenderableLight.h"
#include "builder/AbstractBuilder.h"

class PointLight : public AbstractRenderableLight {
	private:
		Attenuation attenuation = {1.0f, 0.1f, 0.01f};

		explicit PointLight(const std::string &name);
		~PointLight() = default;

	public:
		void setAttenuation(const Attenuation &attenuation);
		Attenuation getAttenuation();

		std::map<std::string, std::variant<glm::vec3, float>> getShaderVariables() const;

		class Builder : public AbstractBuilder<PointLight> {
			public:
				Builder(const std::string &name);

				Builder& setColor(const glm::vec3 color);
				Builder& setAmbient(const glm::vec3 ambient);
				Builder& setDiffuse(const glm::vec3 diffuse);
				Builder& setSpecular(const glm::vec3 specular);
				Builder& setAttenuation(const Attenuation &attenuation);
				Builder& setTransformation(Transform::Composite* composite);

				PointLight* build() override;
	};

	static Builder createLight(const std::string &name);
};
