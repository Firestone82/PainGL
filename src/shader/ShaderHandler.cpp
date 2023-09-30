#include "ShaderHandler.h"

#include <fstream>
#include <sstream>

ShaderHandler::ShaderHandler() {
    // Empty
}

ShaderHandler::~ShaderHandler() {
    fprintf(stdout, "[DEBUG] Destroying %zu shaders\n", shaders.size());

    for (auto& shader : shaders) {
        fprintf(stdout, "[DEBUG] - Shader %s destroyed\n", shader->getName().c_str());
        delete shader;
    }
}

void ShaderHandler::loadShaderVar(const std::string& name, const char* source, GLenum type) {
    fprintf(stdout, "[DEBUG] Loading shader \"%s\"\n", name.c_str());

    Shader* shader = new Shader(name, type, source);
    shaders.push_back(shader);
}

void ShaderHandler::loadShaderFile(const std::string &name, const std::string &path, GLenum type) {
    fprintf(stdout, "[DEBUG] Loading shader \"%s\" from file \"%s\"\n", name.c_str(), path.c_str());

    std::ifstream file(path);
    if (!file.is_open()) {
        fprintf(stderr, "[ERROR] Failed to open file \"%s\"\n", path.c_str());
        return;
    }

    std::stringstream stream;
    stream << file.rdbuf();
    std::string source = stream.str();

    Shader* shader = nullptr;
    try {
        shader = new Shader(name, type, source.c_str());
    } catch (const std::exception& e) {
        fprintf(stderr, "[ERROR]  - Failed to load shader \"%s\": %s\n", name.c_str(), e.what());
        return;
    }

    shaders.push_back(shader);
    fprintf(stdout, "[DEBUG]  - Successfully loaded shader.\n");

    file.close();
}

std::vector<Shader*> ShaderHandler::getShaders() const {
    return this->shaders;
}

Shader* ShaderHandler::getShader(const std::string &name) const {
    for (auto shader : shaders) {
        if (shader->getName() == name) {
            return shader;
        }
    }

    return nullptr;
}

Program* ShaderHandler::createProgram(const std::string &fragment, const std::string &vertex) const {
    Program* program = new Program();

    program->attach(getShader(fragment));
    program->attach(getShader(vertex));
    program->link();

    return program;
}