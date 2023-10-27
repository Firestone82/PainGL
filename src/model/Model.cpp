#include "model/Model.h"

Model::Model(const std::string &name, const std::vector<float> &points) : name(name) {
	this->points = points;

	vbo = new VBO();
	vbo->bind();
	vbo->setData(points, points.size() * sizeof(float), GL_STATIC_DRAW);

	vao = new VAO();
	vao->bind();

	// Vertex positions
	vao->setEnableVertexArray(0);
	vao->setVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(points[0]) * 6, (GLvoid *) nullptr);

	// Vertex normals
	vao->setEnableVertexArray(1);
	vao->setVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(points[0]) * 6, (GLvoid *) (3 * sizeof(float)));
}

Model::Model(const std::string &name, const std::vector<float> &points, const std::vector<unsigned int> &indices, const std::vector<Texture> &textures) : name(name), object(true) {
	this->points = points;
	this->indices = indices;
	this->textures = textures;

	vbo = new VBO();
	vbo->bind();
	vbo->setData(points, points.size() * sizeof(float), GL_STATIC_DRAW);

	ebo = new EBO();
	ebo->bind();
	ebo->setData(indices, indices.size() * sizeof(unsigned int), GL_STATIC_DRAW);

	vao = new VAO();
	vao->bind();

	// Vertex positions
	vao->setEnableVertexArray(0);
	vao->setVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(points[0]) * 8, (GLvoid*) nullptr);

	// Vertex normals
	vao->setEnableVertexArray(1);
	vao->setVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(points[0]) * 8, (GLvoid*) (3 * sizeof(float)));

	// Vertex texture coordinates
	vao->setEnableVertexArray(2);
	vao->setVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(points[0]) * 8, (GLvoid*) (6 * sizeof(float)));
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