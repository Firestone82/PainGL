#pragma once

#include "scene/light/AbstractRenderableLight.h"
#include "builder/AbstractBuilder.h"

class SpotLight : public AbstractRenderableLight {
	private:
		glm::vec3 direction = glm::vec3(0.0f, 0.0f, 0.0f);
		glm::vec2 cutOff = {18.0f, 30.0f};
		Attenuation attenuation = {1.0f, 0.1f, 0.01f};

		explicit SpotLight(const std::string &name);
		~SpotLight() = default;

	public:
		void setDirection(const glm::vec3 direction);
		glm::vec3 getDirection();

		void setAttenuation(const Attenuation &attenuation);
		Attenuation getAttenuation();

		void setCutOff(float cutOff);
		float getCutOff();

		void setOuterCutOff(float outerCutOff);
		float getOuterCutOff();

		std::map<std::string, std::variant<glm::vec3, float>> getShaderVariables() const;

		class Builder : public AbstractBuilder<SpotLight> {
			public:
				Builder(const std::string &name);

				Builder& setColor(const glm::vec3 color);
				Builder& setAmbient(const glm::vec3 ambient);
				Builder& setDiffuse(const glm::vec3 diffuse);
				Builder& setSpecular(const glm::vec3 specular);
				Builder& setDirection(const glm::vec3 direction);
				Builder& setAttenuation(const Attenuation &attenuation);
				Builder& setTransformation(Transform::Composite* composite);
				Builder& setCutOff(float cutOff);
				Builder& setOuterCutOff(float outerCutOff);

				SpotLight* build() override;
		};

	static Builder createLight(const std::string &name);
};
