#include "model/ModelHandler.h"
#include "Logger.h"

#include <filesystem>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

ModelHandler::~ModelHandler() {
    Logger::info("\nDestroying %zu models", models.size());

    for (auto &model: models) {
        Logger::info(" - Model %s destroyed", model->getName().c_str());
        delete model;
    }
}

void ModelHandler::loadModelFolder(const std::string& folderPath, const std::string& extension) {
    Logger::info(R"(\nLoading models from "%s")", folderPath.c_str());

    for (const auto &entry: std::filesystem::directory_iterator(folderPath)) {
        if (entry.is_regular_file() && entry.path().extension() == extension) {
            std::string modelName = entry.path().stem().string();
            std::string modelPath = entry.path().string();

            loadModelFile(modelName, modelPath);
        }
    }
}

void ModelHandler::loadModelFile(const std::string &name, const std::string &path) {
    Logger::info(R"(Loading model "%s" from file "%s")", name.c_str(), path.c_str());

    Assimp::Importer importer;
    const aiScene *scene = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs);

    if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) {
        Logger::error(R"( -  Failed to load model "%s": %s)", name.c_str(), importer.GetErrorString());
        return;
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

    Model *model = nullptr;
    try {
        model = new Model(name, points, indices);
    } catch (const std::exception &e) {
        Logger::error(R"( - Failed to load model "%s": %s)", name.c_str(), e.what());
        return;
    }

    models.push_back(model);
    Logger::info(" - Successfully loaded model. Size: %zu (%dB)", model->getPoints().size(), model->getSize());
}

void ModelHandler::loadModelVariable(const std::string &name, const std::vector<float> &points) {
    Logger::info(R"(Loading model "%s")", name.c_str());

    Model* model = nullptr;
    try {
        model = new Model(name, points);
    } catch (const std::exception &e) {
        Logger::error(R"( - Failed to load model "%s": %s)", name.c_str(), e.what());
        return;
    }

    models.push_back(model);
    Logger::info(" - Successfully loaded model. Size: %lu (%dB)", model->getPoints().size(), model->getSize());
}

std::vector<Model*> ModelHandler::getModels() const {
    return this->models;
}

Model* ModelHandler::getModel(const std::string &name) const {
    for (auto model: models) {
        if (model->getName() == name) {
            return model;
        }
    }

    return nullptr;
}