#pragma once

#include "model/Model.h"
#include <vector>
#include <string>

class ModelHandler {
    private:
        std::vector<Model*> models;

    public:
        ModelHandler() = default;
        ~ModelHandler();

        void loadModelFolder(const std::string &folderPath, const std::string& extension);
        void loadModelFile(const std::string &name, const std::string &path);
        void loadModelVariable(const std::string &name, const std::vector<float>& points, GLulong size);

        std::vector<Model*> getModels() const;
        Model* getModel(const std::string &name) const;
};
