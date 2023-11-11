#pragma once

#define GLEW_STATIC
#include <GL/glew.h>
#include <vector>

class EBO {
    private:
        GLuint ebo = 0;

    public:
        EBO();
        ~EBO();

        void setData(const void* data, GLulong size, GLenum mode = GL_STATIC_DRAW);

        void bind();
		void unbind();
};
