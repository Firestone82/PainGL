#pragma once

#include "buffer/VAO.h"
#include "buffer/VBO.h"
#include "buffer/EBO.h"
#include "texture/Texture.h"

#include <string>
#include <glm/glm.hpp>

class Model {
	private:
		std::string name;
		bool object = false;

		VAO* vao;
		VBO* vbo;
		EBO* ebo;

		std::vector<float> points;
		std::vector<unsigned int> indices;
		std::vector<Texture> textures;

	public:
		Model(const std::string &name, const std::vector<float> &points);
		Model(const std::string &name, const std::vector<float> &points,
									   const std::vector<unsigned int> &indices,
									   const std::vector<Texture> &textures);
		~Model();

		std::string getName() const;
		bool hasIndices() const;

		VAO* getVAO() const;
		VBO* getVBO() const;
		EBO* getEBO() const;

		std::vector<float> getPoints() const;
		std::vector<unsigned int> getIndices() const;
		std::vector<Texture> getTextures() const;
		GLsizei getSize() const;
};
