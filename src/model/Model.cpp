#include "model/Model.h"
#include "utils/Logger.h"

Model::Model(const Path &filePath) : filePath(filePath) {
	// Empty
}

Model::~Model() {
	for (Mesh* mesh: this->meshes) {
		delete mesh;
	}

	delete this->boundingBox;
}

std::string Model::getName() const {
	return this->filePath.getFileNameWithoutExtension();
}

Path Model::getFilePath() const {
	return this->filePath;
}

void Model::addMesh(Mesh* mesh) {
	this->meshes.push_back(mesh);
}

Mesh* Model::getMesh(int index) const {
	return this->meshes[index];
}

std::vector<Mesh*> Model::getMeshes() const {
	return this->meshes;
}

void Model::setBoundingBox(BoundingBox* boundingBox) {
	this->boundingBox = boundingBox;
}

BoundingBox* Model::getBoundingBox() const {
	return this->boundingBox;
}