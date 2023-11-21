#include "scene/transformation/curve/BalisticCurve.h"
#include "Engine.h"

namespace Transform {
	BalisticCurve::BalisticCurve(glm::vec3 position, glm::vec3 direction, float speed) : Component(Transform::Type::CURVE, nullptr) {
		this->position = position;
		this->direction = direction;
		this->speed = speed;

		calculate();

	}

	void BalisticCurve::calculate() {
		float deltaTime = Engine::getInstance()->getDeltaTime();

		glm::vec3 velocity = direction * speed;
		glm::vec3 acceleration = gravity;

		position += velocity * deltaTime + 0.5f * acceleration * deltaTime * deltaTime;
		direction += acceleration * deltaTime;

		this->matrix = glm::mat4(1.0f);
		this->matrix = glm::translate(this->matrix, position);
	}

	Component* BalisticCurve::clone() {
		return new BalisticCurve(*this);
	}

	void BalisticCurve::draw() {

	}
}