#pragma once

#define GLEW_STATIC
#include <GL/glew.h>

class VAO {
    private:
        GLuint vao = 0;

    public:
        VAO();
        ~VAO();

        void setEnableVertexArray(int index);
        void setVertexAttribPointer(int index, int size, GLenum type, GLboolean normalized, GLsizei stride, const void* pointer);

        void bind();
};
