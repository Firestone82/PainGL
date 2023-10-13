#include "buffer/VAO.h"

VAO::VAO() {
    glGenVertexArrays(1, &this->vao);
}

VAO::~VAO() {
    glDeleteVertexArrays(1, &this->vao);
    this->vao = 0;
}

void VAO::setEnableVertexArray(int index) {
    glEnableVertexAttribArray(index);
}

void VAO::setVertexAttribPointer(int index, int size, GLenum type, GLboolean normalized, GLsizei stride, const void* pointer) {
    glVertexAttribPointer(index, size, type, normalized, stride, pointer);
}

void VAO::bind() {
    glBindVertexArray(this->vao);
}
