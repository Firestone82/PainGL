#pragma once

#include "model/Model.h"
#include <vector>
#include <string>

class ModelHandler {
    private:
        std::vector<Model*> models;

    public:
        ModelHandler();
        ~ModelHandler();

        void loadModelFile(const std::string& name, const std::string& path);
        void loadModelVar(const std::string& name, const float* data, int dataSize, int vertexCount);

        std::vector<Model*> getModels() const;
        Model* getModel(const std::string& name) const;
};
