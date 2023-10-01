#include "ModelHandler.h"

#include <filesystem>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

ModelHandler::~ModelHandler() {
    fprintf(stdout, "[DEBUG] Destroying %zu models\n", models.size());

    for (auto &model: models) {
        fprintf(stdout, "[DEBUG] - Model %s destroyed\n", model->getName().c_str());
        delete model;
    }
}

void ModelHandler::loadModelFolder(const std::string& folderPath, const std::string& extension) {
    fprintf(stdout, "[DEBUG] Loading models from \"%s\"\n", folderPath.c_str());

    for (const auto &entry: std::filesystem::directory_iterator(folderPath)) {
        if (entry.is_regular_file() && entry.path().extension() == extension) {
            std::string modelName = entry.path().stem().string();
            std::string modelPath = entry.path().string();

            loadModelFile(modelName, modelPath);
        }
    }
}

void ModelHandler::loadModelFile(const std::string &name, const std::string &path) {
    fprintf(stdout, "[DEBUG] Loading model \"%s\" from file \"%s\"\n", name.c_str(), path.c_str());

    Assimp::Importer importer;
    const aiScene *scene = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs);

    if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) {
        fprintf(stderr, "[ERROR] Failed to load model \"%s\": %s\n", name.c_str(), importer.GetErrorString());
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

    Model* model = nullptr;
    try {
        model = new Model(name, points, indices, points.size());
    } catch (const std::exception &e) {
        fprintf(stderr, "[ERROR]  - Failed to load model \"%s\": %s\n", name.c_str(), e.what());
        return;
    }

    models.push_back(model);
    fprintf(stdout, "[DEBUG]  - Successfully loaded model. Size: %zu (%d)\n", points.size(), model->getVerticesCount());
}

void ModelHandler::loadModelVariable(const std::string &name, const std::vector<float>& points, GLulong size) {
    fprintf(stdout, "[DEBUG] Loading model \"%s\"\n", name.c_str());

    Model* model = nullptr;
    try {
        model = new Model(name, points, size);
    } catch (const std::exception &e) {
        fprintf(stderr, "[ERROR]  - Failed to load model \"%s\": %s\n", name.c_str(), e.what());
        return;
    }

    models.push_back(model);
    fprintf(stdout, "[DEBUG]  - Successfully loaded model. Size: %lu (%d)\n", size, model->getVerticesCount());
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