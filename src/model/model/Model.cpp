#include "Model.h"
#include <GL/glew.h>

Model::Model(const std::string& name, const float* data, int dataSize, int vertexCount) {
    this->dataSize = dataSize;
    this->vertexCount = vertexCount;
    this->name = name;

    vbo = new VBO();
    vbo->bind();
    vbo->setData(data, dataSize, GL_STATIC_DRAW);

    vao = new VAO();
    vao->bind();
    vao->setEnableVertexArray(0);
    vao->setEnableVertexArray(1);
    vao->setVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(data[0])*6, (GLvoid*)0);
    vao->setVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(data[0])*6, (GLvoid*)(3*4));
}

Model::~Model() {
    delete vao;
    this->vao = nullptr;

    delete vbo;
    this->vbo = nullptr;
}

std::string Model::getName() const {
    return this->name;
}

VAO* Model::getVAO() const {
    return this->vao;
}

VBO* Model::getVBO() const {
    return this->vbo;
}

int Model::getDataSize() const {
    return this->dataSize;
}

int Model::getVertexCount() const {
    return this->vertexCount;
}