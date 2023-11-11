#include "scene/light/type/PointLight.h"
#include "Engine.h"
#include "utils/Logger.h"

PointLight::PointLight(const std::string &name) : AbstractRenderableLight(name, LightType::POINT_LIGHT) {
	this->material = Material::createMaterial().build();
	this->shaderProgram = Engine::getInstance()->getShaderHandler()->createProgram("modelShader.vert", "lightModelShader.frag");
	this->model = Engine::getInstance()->getModelHandler()->getModel("pointLight");
};

void PointLight::setAttenuation(const Attenuation &attenuation) {
	this->attenuation = attenuation;
	update();
}

Attenuation PointLight::getAttenuation() {
	return this->attenuation;
}

std::map<std::string, std::variant<glm::vec3, float>> PointLight::getShaderVariables() const {
	std::map<std::string, std::variant<glm::vec3, float>> variables = AbstractRenderableLight::getShaderVariables();
	variables["constant"] = this->attenuation.constant;
	variables["linear"] = this->attenuation.linear;
	variables["quadratic"] = this->attenuation.quadratic;

	return variables;
}

// -- Builder --

PointLight::Builder::Builder(const std::string &name) {
	this->object = new PointLight(name);
}

PointLight::Builder& PointLight::Builder::setColor(glm::vec3 color) {
	this->object->setColor(color);
	return *this;
}

PointLight::Builder& PointLight::Builder::setAmbient(glm::vec3 ambient) {
	this->object->ambient = ambient;
	return *this;
}

PointLight::Builder& PointLight::Builder::setDiffuse(glm::vec3 diffuse) {
	this->object->diffuse = diffuse;
	return *this;
}

PointLight::Builder& PointLight::Builder::setSpecular(glm::vec3 specular) {
	this->object->specular = specular;
	return *this;
}

PointLight::Builder& PointLight::Builder::setAttenuation(const Attenuation &attenuation) {
	this->object->attenuation = attenuation;
	return *this;
}

PointLight::Builder& PointLight::Builder::setTransformation(Transform::Composite* composite) {
	this->object->transformation->setTransformation(composite);
	return *this;
}

PointLight* PointLight::Builder::build() {
	this->object->material->setDiffuseColor(this->object->getColor());
	return this->object;
}

PointLight::Builder PointLight::createLight(const std::string &name) {
	return Builder(name);
}
