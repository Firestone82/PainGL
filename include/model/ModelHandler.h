#pragma once

#include "model/Model.h"

#include <vector>
#include <string>

class ModelHandler {
	private:
		Path folderPath;
		std::vector<Model*> models;

	public:
		ModelHandler(const Path &folderPath, bool preLoad = false);
		~ModelHandler();

		void loadModelFolder(const Path &folderPath);

		Model* loadModelFile(const Path &filePath);
		Model* loadModelVariable(const std::string &name, const std::vector<float> &points);

		std::vector<Model*> getModels() const;
		Model* getModel(const std::string &name);

		Path getFolderPath() const;
};