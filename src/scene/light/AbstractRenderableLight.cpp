#include "scene/light/AbstractRenderableLight.h"

AbstractRenderableLight::AbstractRenderableLight(const std::string &name, LightType type) : AbstractLight(name, type) {
	// EMPTY
}

std::map<std::string, std::variant<glm::vec3, float>> AbstractRenderableLight::getShaderVariables() const {
	std::map<std::string, std::variant<glm::vec3, float>> variables = AbstractLight::getShaderVariables();
	variables["position"] = this->getPosition();

	return variables;
}