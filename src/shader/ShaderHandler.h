#pragma once

#include "shader/Shader.h"
#include "program/Program.h"
#include <vector>

class ShaderHandler {
    private:
        std::vector<Shader*> shaders;

    public:
        ShaderHandler();
        ~ShaderHandler();

        void loadShaderVar(const std::string& name, const char* source, GLenum type);
        void loadShaderFile(const std::string& name, const std::string& path, GLenum type);

        std::vector<Shader*> getShaders() const;
        Shader* getShader(const std::string& name) const;

        Program* createProgram(const std::string& fragment, const std::string& vertex) const;
};
