#include "scene/entity/material/Material.h"
#include "Engine.h"
#include "utils/Logger.h"

void Material::setDiffuseColor(glm::vec3 color) {
	this->diffuseColor = color;
}

glm::vec3 Material::getDiffuseColor() const {
	return this->diffuseColor;
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

void Material::addTexture(const std::string &texture, TextureType type) {
	Texture* tex = Engine::getInstance()->getTextureHandler()->getTexture(texture);

	if (tex == nullptr) {
		Logger::warning("%s | Texture \"%s\" not found", __THIS_FUNC_C__, texture.c_str());
		return;
	}

	this->overrideTextures.push_back(tex);
}

void Material::addTexture(Texture* texture) {
	this->overrideTextures.push_back(texture);
}

std::vector<Texture*> Material::getTextures() const {
	return this->overrideTextures;
}

// -- Builder --

Material::Builder::Builder() {
	this->material = new Material();
}

Material::Builder& Material::Builder::setDiffuseColor(glm::vec3 color) {
	this->material->diffuseColor = color;
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

Material::Builder& Material::Builder::addTexture(const std::string &texture, TextureType type) {
	Texture* tex = Engine::getInstance()->getTextureHandler()->getTexture(texture);

	if (tex == nullptr) {
		Logger::warning("%s | Texture \"%s\" not found", __THIS_FUNC_C__, texture.c_str());
		return *this;
	}

	this->material->overrideTextures.push_back(tex);
	return *this;
}

Material* Material::Builder::build() {
	return this->material;
}

Material::Builder Material::createMaterial() {
	return Material::Builder();
}