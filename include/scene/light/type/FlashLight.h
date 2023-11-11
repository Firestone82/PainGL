#pragma once

#include "scene/light/AbstractLight.h"
#include "builder/AbstractBuilder.h"

class FlashLight : public AbstractLight {
	private:
		glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f);
		glm::vec3 direction = glm::vec3(0.0f, 0.0f, 0.0f);
		glm::vec2 cutOff = {18.0f, 20.0f};
		Attenuation attenuation = {1.0f, 0.1f, 0.01f};

		explicit FlashLight(const std::string &name);
		~FlashLight() = default;

	public:
		glm::vec3 getDirection();

		void setAttenuation(const Attenuation &attenuation);
		Attenuation getAttenuation();

		void setCutOff(float cutOff);
		float getCutOff();

		void setOuterCutOff(float outerCutOff);
		float getOuterCutOff();

		std::map<std::string, std::variant<glm::vec3, float>> getShaderVariables() const;

		class Builder : public AbstractBuilder<FlashLight> {
			public:
				Builder(const std::string &name);

				Builder& setColor(const glm::vec3 color);
				Builder& setAmbient(const glm::vec3 ambient);
				Builder& setDiffuse(const glm::vec3 diffuse);
				Builder& setSpecular(const glm::vec3 specular);
				Builder& setAttenuation(const Attenuation &attenuation);
				Builder& setCutOff(float cutOff);
				Builder& setOuterCutOff(float outerCutOff);

				FlashLight* build() override;
		};

		static Builder createLight(const std::string &name);
};