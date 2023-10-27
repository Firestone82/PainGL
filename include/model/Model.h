#pragma once

#include "buffer/VAO.h"
#include "buffer/VBO.h"
#include "buffer/EBO.h"

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

	public:
		Model(const std::string &name, const std::vector<float> &points);
		Model(const std::string &name, const std::vector<float> &points, const std::vector<unsigned int> &indices);
		~Model();

		std::string getName() const;
		bool hasIndices() const;

		VAO* getVAO() const;
		VBO* getVBO() const;
		EBO* getEBO() const;

		std::vector<float> getPoints() const;
		std::vector<unsigned int> getIndices() const;
		GLsizei getSize() const;
};
