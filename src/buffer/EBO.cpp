#include "EBO.h"

EBO::EBO() {
    this->ebo = 0;
    glGenBuffers(1, &this->ebo);
}

EBO::~EBO() {
    glDeleteBuffers(1, &this->ebo);
    this->ebo = 0;
}

void EBO::setData(std::vector<unsigned int> points, GLint size, GLenum usage) {
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, points.data(), usage);
}

void EBO::bind() {
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->ebo);
}

GLuint EBO::get() const {
    return this->ebo;
}