#include "VBO.h"

VBO::VBO() {
    this->vbo = 0;
    glGenBuffers(1, &this->vbo);
}

VBO::~VBO() {
    glDeleteBuffers(1, &this->vbo);
    this->vbo = 0;
}

void VBO::setData(std::vector<float> points, GLulong size, GLenum usage) {
    glBufferData(GL_ARRAY_BUFFER, size, points.data(), usage);
}

void VBO::bind() {
    glBindBuffer(GL_ARRAY_BUFFER, this->vbo);
}