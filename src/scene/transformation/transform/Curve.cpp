#include "scene/transformation/transform/Curve.h"
#include "Engine.h"

namespace Transform {
	Curve::Curve(std::vector<glm::vec3> points, float precision) : Component(Transform::Type::CURVE, nullptr) {
		this->precision = precision;
		this->speed = 1.0f;
		this->curve = new BezierCurve(points);
		this->curve->setResolution(precision);
		calculate();
	}

	Curve::Curve(std::vector<glm::vec3> points, float precision, float speed) : Component(Transform::Type::CURVE, nullptr) {
		this->precision = precision;
		this->speed = speed;
		this->curve = new BezierCurve(points);
		this->curve->setResolution(precision);
		calculate();
	}

	void Curve::calculate() {
		if (this->curve == nullptr) return;

		static float time = 0.0f;
		time += Engine::getInstance()->getDeltaTime() * this->speed;
		time = fmod(time, 1.0f);

		this->matrix = glm::mat4(1.0f);
		this->matrix = glm::translate(this->matrix, this->curve->getPoint(time));
	}

	BezierCurve& Curve::getCurve() {
		return *this->curve;
	}
}