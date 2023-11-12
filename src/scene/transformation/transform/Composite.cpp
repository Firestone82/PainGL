#include "scene/transformation/transform/Composite.h"

namespace Transform {
	void Composite::innerCalculate(glm::mat4& matrix, const std::vector<Transform::Component*>& transforms) {
		matrix = glm::mat4(1.0f);

		for (const auto& transform : transforms) {
			matrix *= transform->resultMatrix();
		}
	}

	Composite::Composite(const std::vector<Transform::Component*> &transforms) : Component(Transform::Type::COMPOSITE, nullptr) {
		this->transforms = transforms;
		for (auto transform : transforms) {
			transform->setParent(this);
		}

		innerCalculate(this->matrix, this->transforms);
	}

	Composite::~Composite() {
		for (const auto &transform: transforms) {
			delete transform;
		}

		transforms.clear();
	}

	std::vector<Transform::Component*>& Composite::get() {
		return transforms;
	}

	glm::mat4 Composite::resultMatrix() {
		glm::mat4 result = glm::mat4(1.0f);

		for (auto transform : transforms) {
			result *= transform->resultMatrix();
		}

		return result;
	}

	bool Composite::isEmpty() {
		return transforms.empty();
	}

	void Composite::calculate() {
		for (auto transform : transforms) {
			if (transform->getParent() == this) {
				transform->calculate();
			}
		}
	}
}