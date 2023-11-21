#pragma once

#include <glm/vec3.hpp>
#include <glm/mat4x4.hpp>
#include <vector>
#include "buffer/VAO.h"
#include "buffer/VBO.h"

class ShaderProgram;
class BoundingBox {
	private:
		glm::vec3 min;
		glm::vec3 max;

		// Renderable
		ShaderProgram* shaderProgram = nullptr;
		std::vector<glm::vec3> points;
		VAO* vao = nullptr;
		VBO* vbo = nullptr;

	public:
		BoundingBox(glm::vec3 min, glm::vec3 max);
		~BoundingBox();

		glm::vec3 getMin() const;
		glm::vec3 getMax() const;

		bool intersects(const BoundingBox& other) const;
		bool isInside(const glm::vec3 point) const;

		void draw(glm::mat4 modelMatrix);
		BoundingBox get(glm::mat4 modelMatrix);
};