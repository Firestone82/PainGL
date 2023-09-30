#pragma once

#include <GL/glew.h>

class VBO {
    private:
        GLuint vbo = 0;

    public:
        VBO();
        ~VBO();

        void setData(const float* data, GLint size, GLenum usage);

        void bind();
        GLuint get() const;
};
