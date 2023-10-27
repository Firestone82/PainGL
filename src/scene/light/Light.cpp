#include "scene/light/Light.h"
#include "Engine.h"

Light::~Light() {
	delete this->transformation;
}

void Light::draw() {

}

void Light::setColor(glm::vec3 rgb) {
	this->color = rgb;
}

glm::vec3 Light::getColor() const {
	return this->color;
}

// -- Builder --

Light::Builder::Builder(const std::string &name) {
	this->light = new Light(name);
}

Light::Builder* Light::Builder::setColor(glm::vec3 color) {
	this->light->color = color;
	return this;
}

Light::Builder* Light::Builder::setTransformation(Transform::Composite* composite) {
	this->light->transformation->setTransformation(composite);
	return this;
}

Light::Builder* Light::Builder::setSimulateFunction(const std::function<void(Light*, float)>& simulateFunction) {
	this->light->simulateFunction = simulateFunction;
	return this;
}

Light* Light::Builder::build() {
	return this->light;
}

Light::Builder* Light::createLight(const std::string &name) {
	return new Light::Builder(name);
}
