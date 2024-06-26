#include "model/ModelHandler.h"
#include "utils/FileUtils.hpp"
#include "utils/Logger.h"
#include "utils/StringUtils.h"
#include "buffer/Vertex.h"
#include "Engine.h"

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

ModelHandler::ModelHandler(const Path &folderPath, bool preLoad) : folderPath(folderPath) {
	if (preLoad) this->loadModelFolder(folderPath);
}

ModelHandler::~ModelHandler() {
	Logger::debug("\nDestroying %zu models", this->models.size());

	for (Model* model : this->models) {
		std::string name = model->getName();
		delete model;
		Logger::debug(R"( - Model "%s" destroyed)", name.c_str());
	}
}

void ModelHandler::loadModelFolder(const Path &folderPath) {
	for (const auto &path: FileUtils::getFiles(folderPath, ".obj")) {
		this->loadModelFile(path);
	}

	// For blank line
	Logger::debug("");
}

void loadMaterialTextures(aiMaterial* material, aiTextureType type, const std::string& directory, std::vector<Texture*>& textures, TextureType textureType) {
	for (GLuint i = 0; i < material->GetTextureCount(type); i++) {
		aiString str;
		material->GetTexture(type, i, &str);

		bool skip = false;
		for (Texture* texture : textures) {
			if (texture->getName() == str.C_Str()) {
				textures.push_back(texture);
				skip = true;
				break;
			}
		}

		if (skip) continue;

		TextureHandler* textureHandler = Engine::getInstance()->getTextureHandler();
		for (Texture* texture : textureHandler->getTextures()) {
			std::string strWithoutExtension = str.C_Str();
			strWithoutExtension = strWithoutExtension.substr(0, strWithoutExtension.find_last_of('.'));

			if (texture->getName() == strWithoutExtension.c_str()) {
				textures.push_back(texture);
				skip = true;
				break;
			}
		}

		if (skip) continue;

		Texture* texture = Engine::getInstance()->getTextureHandler()->loadTextureFile(Path(directory + "/" + str.C_Str()), textureType);
		if (texture != nullptr) {
			textures.push_back(texture);
			Logger::debug(" - Attaching texture from %s \"%s\"", texture->getTextureTypeString().c_str(), str.C_Str());
		}
	}
}

Model* ModelHandler::loadModelFile(const Path &filePath) {
	Logger::debug(R"(Loading model "%s")", filePath.toString().c_str());

	Assimp::Importer importer;
	const aiScene *scene = importer.ReadFile(filePath.toString().c_str(), aiProcess_Triangulate
		| aiProcess_FlipUVs
		| aiProcess_SplitLargeMeshes
		| aiProcess_OptimizeMeshes
	);

	if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) {
		Logger::error(R"( - Failed to load model: %s)", importer.GetErrorString());
		return nullptr;
	}

	Model* model = new Model(filePath);
	this->models.push_back(model);

	for (GLuint i = 0; i < scene->mNumMeshes; i++) {
		aiMesh* mesh = scene->mMeshes[i];

		std::vector<Vertex> points;
		std::vector<GLuint> indices;
		std::vector<Texture*> textures;

		for (GLuint i = 0; i < mesh->mNumVertices; i++) {
			Vertex vertex;

			if (mesh->HasPositions()) {
				vertex.position = glm::vec3(mesh->mVertices[i].x, mesh->mVertices[i].y, mesh->mVertices[i].z);
			} else {
				vertex.position = glm::vec3(0.0f);
			}

			if (mesh->HasNormals()) {
				vertex.normal = glm::vec3(mesh->mNormals[i].x, mesh->mNormals[i].y, mesh->mNormals[i].z);
			} else {
				vertex.normal = glm::vec3(0.0f);
			}

			if (mesh->HasTextureCoords(0)) {
				vertex.texCoords = glm::vec2(mesh->mTextureCoords[0][i].x, mesh->mTextureCoords[0][i].y);
			} else {
				vertex.texCoords = glm::vec2(0.0f);
			}

			points.emplace_back(vertex);
		}

		for (GLuint i = 0; i < mesh->mNumFaces; i++) {
			aiFace face = mesh->mFaces[i];

			for (GLuint k = 0; k < face.mNumIndices; k++) {
				indices.push_back(face.mIndices[k]);
			}
		}

		if (mesh->mMaterialIndex >= 0) {
			aiMaterial* mat = scene->mMaterials[mesh->mMaterialIndex];
			std::string directory = filePath.getDirectory();

			loadMaterialTextures(mat, aiTextureType_DIFFUSE, directory, textures, TextureType::DIFFUSE);
			loadMaterialTextures(mat, aiTextureType_SPECULAR, directory, textures, TextureType::SPECULAR);
		}

		model->addMesh(new Mesh(points, indices, textures));
	}


	glm::vec3 minPoint = {FLT_MAX, FLT_MAX, FLT_MAX};
	glm::vec3 maxPoint = {-FLT_MAX, -FLT_MAX, -FLT_MAX};

	for (Mesh* mesh : model->getMeshes()) {
		for (Vertex vertex : mesh->getVertices()) {
			minPoint.x = std::min(minPoint.x, vertex.position.x);
			minPoint.y = std::min(minPoint.y, vertex.position.y);
			minPoint.z = std::min(minPoint.z, vertex.position.z);

			maxPoint.x = std::max(maxPoint.x, vertex.position.x);
			maxPoint.y = std::max(maxPoint.y, vertex.position.y);
			maxPoint.z = std::max(maxPoint.z, vertex.position.z);
		}
	}

	model->setBoundingBox(new BoundingBox(minPoint, maxPoint));

	Logger::debug(" - Successfully loaded model.");
	return model;
}

Model* ModelHandler::loadModelVariable(const std::string &name, const std::vector<float> &points) {
	Logger::debug(R"(Loading model "%s")", name.c_str());

	std::vector<Vertex> vertices;
	for (GLuint i = 0; i < points.size(); i += 6) {
		Vertex vertex;

		vertex.position = glm::vec3(points[i], points[i + 1], points[i + 2]);
		vertex.normal = glm::vec3(points[i + 3], points[i + 4], points[i + 5]);
		vertex.texCoords = glm::vec2(0.0f);

		vertices.push_back(vertex);
	}

	Model* model = new Model(Path(name));
	model->addMesh(new Mesh(vertices, std::vector<GLuint>(), std::vector<Texture*>()));

	this->models.push_back(model);
	Logger::debug(" - Successfully loaded model.");
	return model;
}

std::vector<Model*> ModelHandler::getModels() const {
	return this->models;
}

Model* ModelHandler::getModel(const std::string &name) {
	for (Model* model : this->models) {
		if (model->getName() == name) {
			return model;
		}
	}

	std::optional<Path> filePath = FileUtils::findFileInFolder(this->folderPath, name, ".obj");

	if (filePath.has_value()) {
		return this->loadModelFile(filePath.value());
	}

	return nullptr;
}