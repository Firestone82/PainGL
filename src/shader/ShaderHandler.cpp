#include "shader/ShaderHandler.h"
#include "event/type/CameraEvents.h"
#include "utils/StringUtils.h"
#include "utils/FileUtils.hpp"
#include "utils/Logger.h"
#include "Engine.h"

ShaderHandler::ShaderHandler(const Path &folderPath, bool preLoad) : folderPath(folderPath) {
	if (preLoad) this->loadShaderFolder(folderPath);
}

ShaderHandler::~ShaderHandler() {
	Logger::debug("\nDestroying %zu shaders", shaders.size());

	for (auto &shader: shaders) {
		std::string name = shader->getName();
		delete shader;
		Logger::debug(R"( - Shader "%s" destroyed)", name.c_str());
	}
}

void ShaderHandler::loadShaderFolder(const Path &folderPath) {
	for (const auto &filePath: FileUtils::getFiles(folderPath)) {

		GLenum shaderType = 0;
		if (filePath.getExtension() == ".vert") {
			shaderType = GL_VERTEX_SHADER;
		} else if (filePath.getExtension() == ".frag") {
			shaderType = GL_FRAGMENT_SHADER;
		}

		// Skip files that are not shaders
		if (shaderType == 0) {
			continue;
		}

		this->loadShaderFile(filePath, shaderType);
	}

	Logger::debug("");
}

Shader* ShaderHandler::loadShaderFile(const Path &filePath, GLenum type) {
	Logger::debug(R"(Loading shader "%s")", filePath.toString().c_str());

	if (!filePath.exists()) {
		Logger::error(R"( - File does not exist)");
		return nullptr;
	}

	File source = File(filePath);
	if (source.content().empty()) {
		Logger::error(R"( - Failed to load shader)");
		return nullptr;
	}

	Shader* shader = new Shader(filePath.getFileName(), type, source.content().c_str());
	this->shaders.push_back(shader);

	Logger::debug(" - Successfully loaded shader.");
	return shader;
}

std::vector<Shader*> ShaderHandler::getShaders() const {
	return this->shaders;
}

Shader* ShaderHandler::getShader(const std::string &name) {
	for (auto &shader: shaders) {
		if (shader->getName() == name) {
			return shader;
		}
	}

	std::optional<Path> filePath = FileUtils::findFileInFolder(this->folderPath, name);

	if (filePath.has_value()) {
		Path path = filePath.value();
		GLenum type = path.getExtension() == ".vert" ? GL_VERTEX_SHADER : GL_FRAGMENT_SHADER;
		return this->loadShaderFile(path, type);
	}

	return nullptr;
}

ShaderProgram* ShaderHandler::createProgram(const std::string &vertex, const std::string &fragment) {
	std::string programName = vertex + "_" + fragment;

	Logger::debug(R"(Creating shader program "%s" ("%s", "%s"))", programName.c_str(), fragment.c_str(), vertex.c_str());

	// If the program already exists, return it
	if (programs.find(programName) != programs.end()) {
		Logger::debug(" - Shader program already exists.");
		return programs.at(programName);
	}

	Shader* fragmentShader = getShader(fragment);
	if (fragmentShader == nullptr) {
		Logger::error(R"( - Shader "%s" not found!)", fragment.c_str());
		return nullptr;
	}

	Shader* vertexShader = getShader(vertex);
	if (vertexShader == nullptr) {
		Logger::error(R"( - Shader "%s" not found!)", vertex.c_str());
		return nullptr;
	}

	ShaderProgram* program;
	try {
		program = new ShaderProgram(programName);
		program->attach(fragmentShader);
		program->attach(vertexShader);
		program->link();
	} catch (const std::exception &e) {
		Logger::error(R"( - Failed to create shader program "%s": %s)", programName.c_str(), e.what());
		return nullptr;
	}

	Logger::debug(" - Successfully created shader program.");
	programs.insert(std::pair<std::string, ShaderProgram*>(programName, program));
	return program;
}

std::vector<ShaderProgram*> ShaderHandler::getPrograms() const {
	std::vector<ShaderProgram*> result;

	for (const auto &program: programs) {
		result.push_back(program.second);
	}

	return result;
}

Path ShaderHandler::getFolderPath() const {
	return this->folderPath;
}
