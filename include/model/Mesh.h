#pragma once

#include "buffer/VAO.h"
#include "buffer/VBO.h"
#include "buffer/EBO.h"
#include "buffer/Vertex.h"
#include "texture/Texture.h"

class Mesh {
	private:
		VAO* vao;
		VBO* vbo;
		EBO* ebo;

		std::vector<Vertex> vertices;
		std::vector<GLuint> indices;
		std::vector<Texture*> textures;

	public:
		Mesh(const std::vector<Vertex> &vertices, const std::vector<GLuint> &indices, const std::vector<Texture*> &textures);
		~Mesh();

		VAO* getVAO() const;
		VBO* getVBO() const;
		EBO* getEBO() const;

		std::vector<Vertex> getVertices() const;
		std::vector<GLuint> getIndices() const;
		std::vector<Texture*> getTextures() const;
};