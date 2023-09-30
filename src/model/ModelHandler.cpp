#include "ModelHandler.h"

ModelHandler::ModelHandler() {
    // Empty
}

ModelHandler::~ModelHandler() {
    fprintf(stdout, "[DEBUG] Destroying %zu models\n", models.size());

    for (auto& model : models) {
        fprintf(stdout, "[DEBUG] - Model %s destroyed\n", model->getName().c_str());
        delete model;
    }
}

void ModelHandler::loadModelFile(const std::string& name, const std::string& path) {
//    // TODO: Load model from file
//    models.push_back(new Model(name, path, size));
}

void ModelHandler::loadModelVar(const std::string& name, const float* data, int dataSize, int vertexCount) {
    fprintf(stdout, "[DEBUG] Loading model \"%s\"\n", name.c_str());

    Model* model = nullptr;
    try {
        model = new Model(name, data, dataSize, vertexCount);
    } catch (const std::exception& e) {
        fprintf(stderr, "[ERROR]  - Failed to load model \"%s\": %s\n", name.c_str(), e.what());
        return;
    }

    models.push_back(model);
    fprintf(stdout, "[DEBUG]  - Successfully loaded model. Size: %d (%d)\n", dataSize, vertexCount);
}

std::vector<Model*> ModelHandler::getModels() const {
    return this->models;
}

Model* ModelHandler::getModel(const std::string& name) const {
    for (auto model : models) {
        if (model->getName() == name) {
            return model;
        }
    }

    return nullptr;
}