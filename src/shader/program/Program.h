#pragma once

#include "../shader/Shader.h"
#include <vector>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

class Program {
    private:
        std::vector<Shader*> shaders;
        GLuint program;

    public:
        explicit Program();
        ~Program();

        void attach(Shader* shader);
        void setShaderVariableMatrix(const glm::mat4 &matrix, const std::string& variable);

        void link();
        void use();
};
