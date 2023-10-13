#pragma once

#include <GL/glew.h>
#include <vector>

class VBO {
    private:
        GLuint vbo = 0;

    public:
        VBO();
        ~VBO();

        void setData(std::vector<float> points, GLulong size, GLenum usage);

        void bind();
};
