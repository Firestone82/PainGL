#include "scene/light/type/SpotLight.h"
#include "Engine.h"

SpotLight::SpotLight(const std::string &name) : AbstractRenderableLight(name, LightType::SPOT_LIGHT) {
	this->material = Material::createMaterial().build();
	this->shaderProgram = Engine::getInstance()->getShaderHandler()->createProgram("modelShader.vert", "lightModelShader.frag");
	this->model = Engine::getInstance()->getModelHandler()->getModel("spotLight");
};

void SpotLight::setDirection(const glm::vec3 direction) {
	this->direction = direction;
	update();
}

glm::vec3 SpotLight::getDirection() {
	return this->direction;
}

void SpotLight::setAttenuation(const Attenuation &attenuation) {
	this->attenuation = attenuation;
	update();
}

Attenuation SpotLight::getAttenuation() {
	return this->attenuation;
}

void SpotLight::setCutOff(float cutOff) {
	this->cutOff[0] = cutOff;
	update();
}

float SpotLight::getCutOff() {
	return this->cutOff[0];
}

void SpotLight::setOuterCutOff(float outerCutOff) {
	this->cutOff[1] = outerCutOff;
	update();
}

float SpotLight::getOuterCutOff() {
	return this->cutOff[1];
}

std::map<std::string, std::variant<glm::vec3, float>> SpotLight::getShaderVariables() const {
	std::map<std::string, std::variant<glm::vec3, float>> variables = AbstractRenderableLight::getShaderVariables();
	variables["direction"] = this->direction;
	variables["constant"] = this->attenuation.constant;
	variables["linear"] = this->attenuation.linear;
	variables["quadratic"] = this->attenuation.quadratic;
	variables["cutOff"] = this->cutOff[0];
	variables["outerCutOff"] = this->cutOff[1];

	return variables;
}

// -- Builder --

SpotLight::Builder::Builder(const std::string &name) {
	this->object = new SpotLight(name);
}

SpotLight::Builder& SpotLight::Builder::setColor(glm::vec3 color) {
	this->object->setColor(color);
	return *this;
}

SpotLight::Builder& SpotLight::Builder::setAmbient(glm::vec3 ambient) {
	this->object->ambient = ambient;
	return *this;
}

SpotLight::Builder& SpotLight::Builder::setDiffuse(glm::vec3 diffuse) {
	this->object->diffuse = diffuse;
	return *this;
}

SpotLight::Builder& SpotLight::Builder::setSpecular(glm::vec3 specular) {
	this->object->specular = specular;
	return *this;
}

SpotLight::Builder& SpotLight::Builder::setDirection(glm::vec3 direction) {
	this->object->direction = direction;
	return *this;
}

SpotLight::Builder& SpotLight::Builder::setAttenuation(const Attenuation &attenuation) {
	this->object->attenuation = attenuation;
	return *this;
}

SpotLight::Builder& SpotLight::Builder::setCutOff(float cutOff) {
	this->object->cutOff[0] = cutOff;
	return *this;
}

SpotLight::Builder& SpotLight::Builder::setOuterCutOff(float outerCutOff) {
	this->object->cutOff[1] = outerCutOff;
	return *this;
}

SpotLight::Builder& SpotLight::Builder::setTransformation(Transform::Composite* composite) {
	this->object->getTransformation()->setTransformation(composite);
	return *this;
}

SpotLight* SpotLight::Builder::build() {
	this->object->material->setDiffuseColor(this->object->getColor());
	return this->object;
}

SpotLight::Builder SpotLight::createLight(const std::string &name) {
	return Builder(name);
}