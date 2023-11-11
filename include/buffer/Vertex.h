#pragma once

#include <glm/glm.hpp>

struct Vertex {
	public:
		glm::vec3 position;
		glm::vec3 normal;
		glm::vec2 texCoords;
		glm::vec3 tangent;
		glm::vec3 bitangent;

		Vertex() = default;
		Vertex(glm::vec3 position, glm::vec3 normal, glm::vec2 texCoords) : position(position), normal(normal), texCoords(texCoords), tangent(glm::vec3(0.0f)), bitangent(glm::vec3(0.0f)) {}
		Vertex(glm::vec3 position, glm::vec3 normal, glm::vec2 texCoords, glm::vec3 tangent, glm::vec3 bitangent) : position(position), normal(normal), texCoords(texCoords), tangent(tangent), bitangent(bitangent) {}
};