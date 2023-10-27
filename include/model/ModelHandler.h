#pragma once

#include "model/Model.h"

#include <vector>
#include <string>

class ModelHandler {
	private:
		std::string path;
		std::vector<Model*> models;

	public:
		ModelHandler(const std::string path, bool preLoad = false);
		~ModelHandler();

		void loadModelFolder(const std::string &folderPath, const std::string &extension);
		Model* loadModelFile(const std::string &name, const std::string &path);
		Model* loadModelVariable(const std::string &name, const std::vector<float> &points);

		std::vector<Model*> getModels() const;
		Model* getModel(const std::string &name);
};