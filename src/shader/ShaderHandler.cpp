#include "shader/ShaderHandler.h"
#include "Logger.h"

#include <filesystem>
#include <fstream>
#include <sstream>

ShaderHandler::~ShaderHandler() {
    Logger::info("\nDestroying %zu shaders", shaders.size());

    for (auto &shader: shaders) {
        Logger::info(" Shader %s destroyed", shader->getName().c_str());
        delete shader;
    }
}

void ShaderHandler::loadShaderFolder(const std::string &folderPath, const std::string &extension) {
    Logger::info(R"(\nLoading shaders from "%s" with extension "%s")", folderPath.c_str(), extension.c_str());

    for (const auto &entry: std::filesystem::directory_iterator(folderPath)) {
        if (entry.is_regular_file() && entry.path().extension() == extension) {
            std::string shaderName = entry.path().stem().string();
            std::string shaderPath = entry.path().string();

            GLenum shaderType = extension == ".vert" ? GL_VERTEX_SHADER : GL_FRAGMENT_SHADER;
            loadShaderFile(shaderName, shaderPath, shaderType);
        }
    }
}

void ShaderHandler::loadShaderVar(const std::string &name, const char *source, GLenum type) {
    Logger::info(R"(Loading shader "%s")", name.c_str());

    Shader* shader = nullptr;
    try {
        shader = new Shader(name, type, source);
    } catch (const std::exception &e) {
        Logger::error(R"(  - Failed to load shader "%s": %s)", name.c_str(), e.what());
        return;
    }

    shaders.push_back(shader);
    Logger::info(" - Successfully loaded shader.");
}

void ShaderHandler::loadShaderFile(const std::string &name, const std::string &path, GLenum type) {
    Logger::info(R"(Loading shader "%s" from file "%s")", name.c_str(), path.c_str());

    std::ifstream file(path);
    if (!file.is_open()) {
        Logger::info(R"(Failed to open file "%s")", path.c_str());
        return;
    }

    std::stringstream stream;
    stream << file.rdbuf();
    std::string source = stream.str();

    Shader *shader = nullptr;
    try {
        shader = new Shader(name, type, source.c_str());
    } catch (const std::exception &e) {
        Logger::error(R"(  - Failed to load shader "%s": %s)", name.c_str(), e.what());
        return;
    }

    shaders.push_back(shader);
    Logger::info(" - Successfully loaded shader.");

    file.close();
}

std::vector<Shader*> ShaderHandler::getShaders() const {
    return this->shaders;
}

Shader* ShaderHandler::getShader(const std::string &name) const {
    for (auto shader: shaders) {
        if (shader->getName() == name) {
            return shader;
        }
    }

    return nullptr;
}

Program *ShaderHandler::createProgram(const std::string &fragment, const std::string &vertex) const {
    Program* program = new Program();

    program->attach(getShader(fragment));
    program->attach(getShader(vertex));
    program->link();

    return program;
}