#include "scene/entity/material/Material.h"
#include "Engine.h"

Material::~Material() {
	this->diffuseTexture = nullptr;
	this->specularTexture = nullptr;
}

void Material::setDiffuseTexture(Texture* texture) {
	this->diffuseTexture = texture;
}

Texture* Material::getDiffuseTexture() const {
	return this->diffuseTexture;
}

void Material::setDiffuseColor(glm::vec3 color) {
	this->diffuseColor = color;
}

glm::vec3 Material::getDiffuseColor() const {
	return this->diffuseColor;
}

void Material::setSpecularTexture(Texture* texture) {
	this->specularTexture = texture;
}

Texture* Material::getSpecularTexture() const {
	return this->specularTexture;
}

void Material::setSpecularColor(glm::vec3 color) {
	this->specularColor = color;
}

glm::vec3 Material::getSpecularColor() const {
	return this->specularColor;
}

void Material::setShininess(float shininess) {
	this->shininess = shininess;
}

float Material::getShininess() const {
	return this->shininess;
}

void Material::setTextureScale(float scale) {
	this->textureScale = scale;
}

float Material::getTextureScale() const {
	return this->textureScale;
}

// -- Builder --

Material::Builder::Builder() {
	this->material = new Material();
}

Material::Builder& Material::Builder::setDiffuseTexture(Texture* diffuseTexture) {
	this->material->diffuseTexture = diffuseTexture;
	return *this;
}

Material::Builder& Material::Builder::setDiffuseTexture(const std::string &textureName) {
	this->material->diffuseTexture = Engine::getInstance()->getTextureHandler()->getTexture(textureName);
	return *this;
}

Material::Builder& Material::Builder::setDiffuseColor(glm::vec3 color) {
	this->material->diffuseColor = color;
	return *this;
}

Material::Builder& Material::Builder::setSpecularTexture(Texture* specularTexture) {
	this->material->specularTexture = specularTexture;
	return *this;
}

Material::Builder& Material::Builder::setSpecularTexture(const std::string &textureName) {
	this->material->specularTexture = Engine::getInstance()->getTextureHandler()->getTexture(textureName);
	return *this;
}

Material::Builder& Material::Builder::setSpecularColor(glm::vec3 color) {
	this->material->specularColor = color;
	return *this;
}

Material::Builder& Material::Builder::setShininess(float shininess) {
	this->material->shininess = shininess;
	return *this;
}

Material::Builder& Material::Builder::setTextureScale(float scale) {
	this->material->textureScale = scale;
	return *this;
}

Material* Material::Builder::build() {
	return this->material;
}

Material::Builder Material::createMaterial() {
	return Material::Builder();
}