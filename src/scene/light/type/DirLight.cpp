#include "scene/light/type/DirLight.h"

DirLight::DirLight(const std::string &name) : AbstractLight(name, LightType::DIRECTIONAL_LIGHT) {
	// EMPTY
}

void DirLight::setDirection(glm::vec3 direction) {
	this->direction = direction;
	update();
}

glm::vec3 DirLight::getDirection() {
	return this->direction;
}

std::map<std::string, std::variant<glm::vec3, float>> DirLight::getShaderVariables() const {
	std::map<std::string, std::variant<glm::vec3, float>> variables = AbstractLight::getShaderVariables();
	variables["direction"] = this->direction;

	return variables;
}

// -- Builder --

DirLight::Builder::Builder(const std::string &name) {
	this->object = new DirLight(name);
}

DirLight::Builder& DirLight::Builder::setColor(glm::vec3 color) {
	this->object->setColor(color);
	return *this;
}

DirLight::Builder& DirLight::Builder::setAmbient(glm::vec3 ambient) {
	this->object->ambient = ambient;
	return *this;
}

DirLight::Builder& DirLight::Builder::setDiffuse(glm::vec3 diffuse) {
	this->object->diffuse = diffuse;
	return *this;
}

DirLight::Builder& DirLight::Builder::setSpecular(glm::vec3 specular) {
	this->object->specular = specular;
	return *this;
}

DirLight::Builder& DirLight::Builder::setDirection(glm::vec3 direction) {
	this->object->direction = direction;
	return *this;
}

DirLight* DirLight::Builder::build() {
	return this->object;
}

DirLight::Builder DirLight::createLight(const std::string &name) {
	return Builder(name);
}