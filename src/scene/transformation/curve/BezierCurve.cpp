#include "scene/transformation/curve/BezierCurve.h"

#include <math.h>

BezierCurve::BezierCurve(std::initializer_list<glm::vec3> points) : controlPoints(points) {
	// Empty
}

float binomialCoefficient(int n, int k) {
	float result = 1.0f;

	for (int i = 1; i <= k; i++) {
		result *= (float) (n - i + 1) / (float) i;
	}

	return result;
}

glm::vec3 BezierCurve::getPoint(float t) const {
	glm::vec3 point = glm::vec3(0.0f, 0.0f, 0.0f);

	for (int j = 0; j < controlPoints.size(); j++) {
		float binomial = binomialCoefficient(controlPoints.size() - 1, j);
		float power1 = pow(1 - t, controlPoints.size() - 1 - j);
		float power2 = pow(t, j);

		point += binomial * power1 * power2 * controlPoints[j];
	}

	return point;
}

std::vector<glm::vec3> BezierCurve::getControlPoints() const {
	return controlPoints;
}