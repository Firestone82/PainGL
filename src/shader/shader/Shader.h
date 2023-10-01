#pragma once

#include <GL/glew.h>
#include <string>

class Shader {
    private:
        std::string name;

        GLuint shader;
        const char* source;

    public:
        Shader(const std::string &name, GLenum type, const char* source);
        ~Shader();

        std::string getName() const;
        GLenum get() const;
};