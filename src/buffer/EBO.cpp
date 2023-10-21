#include "buffer/EBO.h"

EBO::EBO() {
    this->ebo = 0;
    glGenBuffers(1, &this->ebo);
}

EBO::~EBO() {
    glDeleteBuffers(1, &this->ebo);
    this->ebo = 0;
}

void EBO::setData(std::vector<unsigned int> points, GLulong size, GLenum usage) {
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, points.data(), usage);
}

void EBO::bind() {
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->ebo);
}