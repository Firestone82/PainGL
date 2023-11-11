#pragma once

#include <vector>
#include <glm/vec3.hpp>

class BezierCurve {
	private:
		std::vector<glm::vec3> controlPoints;
		std::vector<glm::vec3> curvePoints;

		int resolution = 200;

		void calculateCurvePoints();

	public:
		BezierCurve(std::vector<glm::vec3> controlPoints);
		~BezierCurve() = default;

		void setResolution(int resolution);
		int getResolution() const;

		std::vector<glm::vec3> getCurvePoints() const;
		std::vector<glm::vec3> getControlPoints() const;
};