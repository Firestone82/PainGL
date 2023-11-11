#include "model/Mesh.h"

Mesh::Mesh(const std::vector<Vertex>& vertices, const std::vector<GLuint>& indices, const std::vector<Texture*>& textures) {
	this->vertices = vertices;
	this->indices = indices;
	this->textures = textures;

	this->vbo = new VBO();
	this->vbo->bind();
	this->vbo->setData(&vertices[0], this->vertices.size() * sizeof(Vertex), GL_STATIC_DRAW);

	if (!indices.empty()) {
		this->ebo = new EBO();
		this->ebo->bind();
		this->ebo->setData(&indices[0], this->indices.size() * sizeof(GLuint), GL_STATIC_DRAW);
	}

	this->vao = new VAO();
	this->vao->bind();

	// Vertex positions
	this->vao->setEnableVertexArray(0);
	this->vao->setVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*) nullptr);

	// Vertex normals
	this->vao->setEnableVertexArray(1);
	this->vao->setVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*) (3 * sizeof(float)));

	// Vertex texture coordinates
	this->vao->setEnableVertexArray(2);
	this->vao->setVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*) (6 * sizeof(float)));
}

Mesh::~Mesh() {
	delete this->vao;
	this->vao = nullptr;

	delete this->vbo;
	this->vbo = nullptr;

	// TODO: Fix crashing
//	if (this->ebo != nullptr) {
//		delete this->ebo;
//		this->ebo = nullptr;
//	}
}

VAO* Mesh::getVAO() const {
	return this->vao;
}

VBO* Mesh::getVBO() const {
	return this->vbo;
}

EBO* Mesh::getEBO() const {
	return this->ebo;
}

std::vector<Vertex> Mesh::getVertices() const {
	return this->vertices;
}

std::vector<GLuint> Mesh::getIndices() const {
	return this->indices;
}

std::vector<Texture*> Mesh::getTextures() const {
	return this->textures;
}