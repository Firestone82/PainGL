#include "buffer/VBO.h"

VBO::VBO() {
    this->vbo = 0;
    glGenBuffers(1, &this->vbo);
}

VBO::~VBO() {
    glDeleteBuffers(1, &this->vbo);
    this->vbo = 0;
}

void VBO::setData(const void* data, GLulong size, GLenum usage) {
    glBufferData(GL_ARRAY_BUFFER, size, data, usage);
}

void VBO::bind() {
    glBindBuffer(GL_ARRAY_BUFFER, this->vbo);
}

void VBO::unbind() {
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}