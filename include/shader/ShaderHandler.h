#pragma once

#include "shader/Shader.h"
#include "shader/ShaderProgram.h"
#include "utils/FileUtils.hpp"

#include <GL/glew.h>
#include <string>
#include <vector>
#include <map>

class ShaderHandler {
	private:
		Path folderPath;
		std::vector<Shader*> shaders;
		std::map<std::string, ShaderProgram*> programs;

	public:
		ShaderHandler(const Path &folderPath, bool preLoad = false);
		~ShaderHandler();

		void loadShaderFolder(const Path &folderPath);
		Shader* loadShaderFile(const Path &filePath, GLenum type);

		std::vector<Shader*> getShaders() const;
		Shader* getShader(const std::string &name);

		ShaderProgram* createProgram(const std::string &vertex, const std::string &fragment);
		std::vector<ShaderProgram*> getPrograms() const;

		Path getFolderPath() const;
};