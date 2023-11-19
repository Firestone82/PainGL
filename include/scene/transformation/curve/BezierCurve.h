#pragma once

#include <vector>
#include <glm/vec3.hpp>
#include <initializer_list>

class BezierCurve {
	private:
		std::vector<glm::vec3> controlPoints;

	public:
		BezierCurve(std::initializer_list<glm::vec3> points);
		~BezierCurve() = default;

		glm::vec3 getPoint(float t) const;
		std::vector<glm::vec3> getControlPoints() const;
};