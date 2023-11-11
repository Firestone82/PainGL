#pragma once

#define GLEW_STATIC
#include <GL/glew.h>
#include <vector>

class VBO {
    private:
        GLuint vbo = 0;

    public:
        VBO();
        ~VBO();

        void setData(const void* data, GLulong size, GLenum usage);

        void bind();
		void unbind();
};
