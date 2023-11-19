#include "scene/transformation/transform/Curve.h"
#include "Engine.h"

namespace Transform {
	Curve::Curve(std::vector<BezierCurve> points, float speed) : Component(Transform::Type::CURVE, nullptr), speed(speed) {
		for (auto point : points) {
			this->curves.push_back(new BezierCurve(point));
		}

		calculate();
	}

	void Curve::calculate() {
		static float time = 0.0f;
		time += Engine::getInstance()->getDeltaTime() * speed;
		time = fmod(time, curves.size());

		int curveID = (int) time;
		float t = time - curveID;

		this->matrix = glm::mat4(1.0f);
		this->matrix = glm::translate(this->matrix, curves[curveID]->getPoint(t));
	}

	Component* Curve::clone() {
		return new Curve(*this);
	}

	void Curve::draw() {
		for (auto curve : curves) {
			curve->draw();
		}
	}
}