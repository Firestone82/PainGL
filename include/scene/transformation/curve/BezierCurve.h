#pragma once

#include <vector>
#include <glm/vec3.hpp>
#include <initializer_list>
#include "scene/structure/Randerable.h"

class BezierCurve {
	private:
		std::vector<glm::vec3> controlPoints;

		// Renderable
		ShaderProgram* shaderProgram = nullptr;
		std::vector<glm::vec3> points;
		VAO* vao = nullptr;
		VBO* vbo = nullptr;

	public:
		BezierCurve(std::initializer_list<glm::vec3> points);
		~BezierCurve();

		glm::vec3 getPoint(float t) const;
		std::vector<glm::vec3> getControlPoints() const;

		void draw();
};