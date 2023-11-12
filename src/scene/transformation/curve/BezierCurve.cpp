#include "scene/transformation/curve/BezierCurve.h"

#include <math.h>

BezierCurve::BezierCurve(std::vector<glm::vec3> controlPoints) : controlPoints(controlPoints) {
	calculateCurvePoints();
}

float binomialCoefficient(int n, int k) {
	if (k == 0 || k == n) {
		return 1;
	}

	return binomialCoefficient(n - 1, k - 1) + binomialCoefficient(n - 1, k);
}

void BezierCurve::calculateCurvePoints() {
	curvePoints.clear();

	for (int i = 0; i <= resolution; i++) {
		float t = (float) i / (float) resolution;

		glm::vec3 point = glm::vec3(0.0f, 0.0f, 0.0f);

		for (int j = 0; j < controlPoints.size(); j++) {
			float binomial = binomialCoefficient(controlPoints.size() - 1, j);
			float power1 = pow(1 - t, controlPoints.size() - 1 - j);
			float power2 = pow(t, j);

			point += binomial * power1 * power2 * controlPoints[j];
		}

		curvePoints.push_back(point);
	}
}

void BezierCurve::setResolution(int resolution) {
	this->resolution = resolution;

	calculateCurvePoints();
}

int BezierCurve::getResolution() const {
	return resolution;
}

glm::vec3 BezierCurve::getPoint(float t) const {
	return curvePoints[(int) (this->curvePoints.size() * t)];
}

std::vector<glm::vec3> BezierCurve::getCurvePoints() const {
	return curvePoints;
}

std::vector<glm::vec3> BezierCurve::getControlPoints() const {
	return controlPoints;
}