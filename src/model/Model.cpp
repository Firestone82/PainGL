#include "model/Model.h"
#include <GL/glew.h>

Model::Model(const std::string &name, const std::vector<float> &data) {
    this->points = data;
    this->name = name;

    vbo = new VBO();
    vbo->bind();
    vbo->setData(data, data.size() * sizeof(float), GL_STATIC_DRAW);

    vao = new VAO();
    vao->bind();
    vao->setEnableVertexArray(0);
    vao->setEnableVertexArray(1);
    vao->setVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(data[0]) * 6, (GLvoid *) nullptr);
    vao->setVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(data[0]) * 6, (GLvoid *) (3 * sizeof(float)));
}

Model::Model(const std::string &name, const std::vector<float> &data, const std::vector<unsigned int> &indices) {
    this->points = data;
    this->indices = indices;
    this->name = name;
    this->object = true;

    vbo = new VBO();
    vbo->bind();
    vbo->setData(data, data.size() * sizeof(float), GL_STATIC_DRAW);

    ebo = new EBO();
    ebo->bind();
    ebo->setData(indices, indices.size() * sizeof(unsigned int), GL_STATIC_DRAW);

    vao = new VAO();
    vao->bind();
    vao->setEnableVertexArray(0);
    vao->setEnableVertexArray(1);
    vao->setVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(data[0]) * 6, (GLvoid *) nullptr);
    vao->setVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(data[0]) * 6, (GLvoid *) (3 * sizeof(float)));
}

Model::~Model() {
    delete vao;
    this->vao = nullptr;

    delete vbo;
    this->vbo = nullptr;

    if (this->object) {
        delete ebo;
        this->ebo = nullptr;
    }
}

std::string Model::getName() const {
    return this->name;
}

bool Model::hasIndices() const {
    return this->object;
}

VAO* Model::getVAO() const {
    return this->vao;
}

VBO* Model::getVBO() const {
    return this->vbo;
}

EBO* Model::getEBO() const {
    return this->ebo;
}

std::vector<float> Model::getPoints() const {
    return this->points;
}

std::vector<unsigned int> Model::getIndices() const {
    return this->indices;
}

GLsizei Model::getSize() const {
    if (this->object) {
        return static_cast<GLsizei>(this->indices.size() * sizeof(unsigned int));
    }

    return static_cast<GLsizei>(this->points.size() * sizeof(float));
}