#include "scene/entity/material/Material.h"

Material::~Material() {
	this->texture = nullptr;
}

void Material::setAmbientColor(glm::vec3 ambientColor) {
	this->ambientColor = ambientColor;
}

glm::vec3 Material::getAmbientColor() const {
	return this->ambientColor;
}

void Material::setObjectColor(glm::vec3 objectColor) {
	this->objectColor = objectColor;
}

glm::vec3 Material::getObjectColor() const {
	return this->objectColor;
}

void Material::setSpecular(float specular) {
	this->specular = specular;
}

float Material::getSpecular() const {
	return this->specular;
}

void Material::setShininess(float shininess) {
	this->shininess = shininess;
}

float Material::getShininess() const {
	return this->shininess;
}

Texture* Material::getTexture() const {
	return this->texture;
}

// -- Builder --

Material::Builder::Builder() {
	this->material = new Material();
}

Material::Builder* Material::Builder::setAmbientColor(glm::vec3 ambientColor) {
	this->material->ambientColor = ambientColor;
	return this;
}

Material::Builder* Material::Builder::setObjectColor(glm::vec3 objectColor) {
	this->material->objectColor = objectColor;
	return this;
}

Material::Builder* Material::Builder::setSpecular(float specular) {
	this->material->specular = specular;
	return this;
}

Material::Builder* Material::Builder::setShininess(float shininess) {
	this->material->shininess = shininess;
	return this;
}

Material::Builder* Material::Builder::setTexture(Texture* texture) {
	this->material->texture = texture;
	return this;
}

Material* Material::Builder::build() {
	return this->material;
}

Material::Builder* Material::createMaterial() {
	return new Material::Builder();
}