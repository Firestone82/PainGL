#include "buffer/EBO.h"

EBO::EBO() {
    this->ebo = 0;
    glGenBuffers(1, &this->ebo);
}

EBO::~EBO() {
    glDeleteBuffers(1, &this->ebo);
    this->ebo = 0;
}

void EBO::setData(const void* data, GLulong size, GLenum usage) {
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, data, usage);
}

void EBO::bind() {
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->ebo);
}

void EBO::unbind() {
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}