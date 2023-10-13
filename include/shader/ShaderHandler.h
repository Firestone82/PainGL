#pragma once

#include "shader/Shader.h"
#include "Program.h"
#include <vector>

class ShaderHandler {
    private:
        std::vector<Shader*> shaders;

    public:
        ShaderHandler() = default;
        ~ShaderHandler();

        void loadShaderFolder(const std::string& folderPath, const std::string& extension);
        void loadShaderVar(const std::string& name, const char* source, GLenum type);
        void loadShaderFile(const std::string& name, const std::string& path, GLenum type);

        std::vector<Shader*> getShaders() const;
        Shader* getShader(const std::string& name) const;

        Program* createProgram(const std::string& fragment, const std::string& vertex) const;
};
