#include "shader/ShaderHandler.h"
#include "utils/Logger.h"
#include "utils/FileUtils.h"
#include "utils/StringUtils.h"
#include "Engine.h"
#include "event/type/CameraEvents.h"

ShaderHandler::ShaderHandler(const std::string &path, bool preLoad) : path(path) {
	if (preLoad) {
		this->loadShaderFolder(path, ".frag");
		this->loadShaderFolder(path, ".vert");
	}
}

ShaderHandler::~ShaderHandler() {
	Logger::debug("\nDestroying %zu shaders", shaders.size());

	for (auto &shader: shaders) {
		std::string name = shader->getName();
		delete shader;
		Logger::debug(R"( - Shader "%s" destroyed)", name.c_str());
	}
}

void ShaderHandler::loadShaderFolder(const std::string &folderPath, const std::string &extension) {
	for (const auto &entry: FileUtils::getFiles(folderPath, extension)) {
		std::vector<std::string> args = StringUtils::split(entry, "\\");

		GLenum shaderType = extension == ".vert" ? GL_VERTEX_SHADER : GL_FRAGMENT_SHADER;
		loadShaderFile(args[1], entry, shaderType);
	}
}

Shader* ShaderHandler::loadShaderVar(const std::string &name, const char* source, GLenum type) {
	Logger::debug(R"(Loading shader "%s")", name.c_str());

	Shader* shader;
	try {
		shader = new Shader(name, type, source);
	} catch (const std::exception &e) {
		Logger::error(R"( - Failed to load shader "%s": %s)", name.c_str(), e.what());
		return nullptr;
	}

	shaders.push_back(shader);
	Logger::debug(" - Successfully loaded shader.");
	return shader;
}

Shader* ShaderHandler::loadShaderFile(const std::string &name, const std::string &path, GLenum type) {
	Logger::debug(R"(Loading shader "%s" from file "%s")", name.c_str(), path.c_str());

	std::string source = FileUtils::readFile(path);
	if (source.empty()) {
		Logger::error(R"( - Failed to load shader "%s": Failed to read file)", name.c_str());
		return nullptr;
	}

	Shader* shader;
	try {
		shader = new Shader(name, type, source.c_str());
	} catch (const std::exception &e) {
		Logger::error(R"( - Failed to load shader "%s": %s)", name.c_str(), e.what());
		return nullptr;
	}

	shaders.push_back(shader);
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

	// Try to load the model if it doesn't exist
	std::string path = this->path + "/" + name;
	if (FileUtils::fileExists(path)) {
		return this->loadShaderFile(name, path, FileUtils::getFileExtension(path) == ".vert" ? GL_VERTEX_SHADER : GL_FRAGMENT_SHADER);
	}

	return nullptr;
}

ShaderProgram *ShaderHandler::createProgram(const std::string &fragment, const std::string &vertex) {
	std::string fragmentName = FileUtils::getFileName(fragment);
	std::string vertexName = FileUtils::getFileName(vertex);
	std::string programName = fragmentName + "-" + vertexName;


	Logger::debug(R"(Creating shader program "%s" with fragment shader "%s" and vertex shader "%s")", programName.c_str(), fragment.c_str(), vertex.c_str());

	// If the program already exists, return it
	if (programs.find(programName) != programs.end()) {
		Logger::debug(" - Shader program already exists.");
		return programs.at(programName);
	}

	Shader* fragmentShader = getShader(fragment);
	if (fragmentShader == nullptr) {
		Logger::error(R"( - Failed to create shader program "%s": Fragment shader "%s" not found)", programName.c_str(), fragment.c_str());
		return nullptr;
	}

	Shader* vertexShader = getShader(vertex);
	if (vertexShader == nullptr) {
		Logger::error(R"( - Failed to create shader program "%s": Vertex shader "%s" not found)", programName.c_str(), vertex.c_str());
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
