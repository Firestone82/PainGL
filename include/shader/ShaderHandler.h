#pragma once

#include "shader/Shader.h"
#include "shader/ShaderProgram.h"

#include <GL/glew.h>
#include <string>
#include <vector>
#include <map>

class ShaderHandler {
	private:
		std::string path;
		std::vector<Shader*> shaders;
		std::map<std::string, ShaderProgram*> programs;

	public:
		ShaderHandler(const std::string &path, bool preLoad = false);
		~ShaderHandler();

		void loadShaderFolder(const std::string &folderPath, const std::string &extension);
		Shader* loadShaderVar(const std::string &name, const char* source, GLenum type);
		Shader* loadShaderFile(const std::string &name, const std::string &path, GLenum type);

		std::vector<Shader*> getShaders() const;
		Shader* getShader(const std::string &name);

		ShaderProgram* createProgram(const std::string &fragment, const std::string &vertex);
		std::vector<ShaderProgram*> getPrograms() const;
};