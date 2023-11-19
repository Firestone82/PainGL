#pragma once

#include <glm/glm.hpp>

struct Vertex {
	public:
		glm::vec3 position;
		glm::vec3 normal;
		glm::vec2 texCoords;

		Vertex() = default;
		Vertex(glm::vec3 position, glm::vec3 normal, glm::vec2 texCoords) : position(position), normal(normal), texCoords(texCoords) {}
};