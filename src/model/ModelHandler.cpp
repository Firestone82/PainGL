#include "model/ModelHandler.h"
#include "utils/FileUtils.h"
#include "utils/Logger.h"
#include "utils/StringUtils.h"

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

ModelHandler::ModelHandler(const std::string path, bool preLoad) : path(path) {
	if (preLoad) {
		this->loadModelFolder(path, ".obj");
	}
}

ModelHandler::~ModelHandler() {
	Logger::debug("\nDestroying %zu models", this->models.size());

	for (Model* model : this->models) {
		std::string name = model->getName();
		delete model;
		Logger::debug(R"( - Model "%s" destroyed)", name.c_str());
	}
}

void ModelHandler::loadModelFolder(const std::string &folderPath, const std::string &extension) {
	for (std::string file : FileUtils::getFiles(folderPath, extension)) {
		std::vector<std::string> args = StringUtils::split(file, "\\");

		this->loadModelFile(args[1], file);
	}
}

Model* ModelHandler::loadModelFile(const std::string &name, const std::string &path) {
	Logger::debug(R"(Loading model "%s" from file "%s")", name.c_str(), path.c_str());

	Assimp::Importer importer;
	const aiScene *scene = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs);

	if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) {
		Logger::error(R"( - Failed to load model "%s": %s)", name.c_str(), importer.GetErrorString());
		return nullptr;
	}

	std::vector<float> points;
	std::vector<unsigned int> indices;
	for (unsigned int i = 0; i < scene->mNumMeshes; i++) {
		aiMesh* mesh = scene->mMeshes[i];

		for (unsigned int j = 0; j < mesh->mNumVertices; j++) {
			points.push_back(mesh->mVertices[j].x);
			points.push_back(mesh->mVertices[j].y);
			points.push_back(mesh->mVertices[j].z);
			points.push_back(mesh->mNormals[j].x);
			points.push_back(mesh->mNormals[j].y);
			points.push_back(mesh->mNormals[j].z);
		}

		for (unsigned int j = 0; j < mesh->mNumFaces; j++) {
			aiFace face = mesh->mFaces[j];

			for (unsigned int k = 0; k < face.mNumIndices; k++) {
				indices.push_back(face.mIndices[face.mNumIndices - k - 1]);
			}
		}
	}

	Model* model;
	try {
		model = new Model(name, points, indices);
	} catch (const std::exception &e) {
		Logger::debug(R"( - Failed to load model "%s": %s)", name.c_str(), e.what());
		return nullptr;
	}

	this->models.push_back(model);
	Logger::debug(" - Successfully loaded model. Size: %zu (%dB)", model->getPoints().size(), model->getSize());
	return model;
}

Model* ModelHandler::loadModelVariable(const std::string &name, const std::vector<float> &points) {
	Logger::debug(R"(Loading model "%s")", name.c_str());

	Model* model;
	try {
		model = new Model(name, points);
	} catch (const std::exception &e) {
		Logger::error(R"( - Failed to load model "%s": %s)", name.c_str(), e.what());
		return nullptr;
	}

	models.push_back(model);
	Logger::debug(" - Successfully loaded model. Size: %lu (%dB)", model->getPoints().size(), model->getSize());
	return model;
}

std::vector<Model*> ModelHandler::getModels() const {
	return this->models;
}

Model* ModelHandler::getModel(const std::string &name) {
	for (auto model: this->models) {
		if (model->getName() == name) {
			return model;
		}
	}

	// Try to load the model if it doesn't exist
	std::string path = this->path + "/" + name + ".obj";
	if (FileUtils::fileExists(path)) {
		return this->loadModelFile(name, path);
	}

	return nullptr;
}