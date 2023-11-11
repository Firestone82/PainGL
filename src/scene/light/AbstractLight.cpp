#include "scene/light/AbstractLight.h"
#include "event/type/LightEvents.h"
#include "Engine.h"

AbstractLight::AbstractLight(const std::string &name, LightType type) : type(type), Object(name) {
	// EMPTY
}

void AbstractLight::setColor(glm::vec3 color) {
	this->ambient = color * 0.1f;
	this->diffuse = color * 0.5f;
	this->specular = this->diffuse * 0.5f;
	update();
}

glm::vec3 AbstractLight::getColor() const {
	return this->ambient * 10.0f;
}

void AbstractLight::setAmbient(glm::vec3 rgb) {
	this->ambient = rgb;
	update();
}

glm::vec3 AbstractLight::getAmbient() const {
	return this->ambient;
}

void AbstractLight::setDiffuse(glm::vec3 rgb) {
	this->diffuse = rgb;
	update();
}

glm::vec3 AbstractLight::getDiffuse() const {
	return this->diffuse;
}

void AbstractLight::setSpecular(glm::vec3 rgb) {
	this->specular = rgb;
	update();
}

glm::vec3 AbstractLight::getSpecular() const {
	return this->specular;
}

LightType AbstractLight::getType() const {
	return this->type;
}

void AbstractLight::update() {
	if (this->getID() < 0) return;
	EventHandler::callEvent(new LightUpdateEvent(this));
}

std::map<std::string, std::variant<glm::vec3, float>> AbstractLight::getShaderVariables() const {
	std::map<std::string, std::variant<glm::vec3, float>> variables;
	variables["ambient"] = this->ambient;
	variables["diffuse"] = this->diffuse;
	variables["specular"] = this->specular;

	return variables;
}