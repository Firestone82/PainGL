#include "scene/transformation/transform/Component.h"

namespace Transform {
	Component::Component(Transform::Type type, std::function<glm::vec3(glm::vec3)> call) {
		this->type = type;
		this->callback = call;
	}

	Transform::Type Component::getType() const {
		return type;
	}

	void Transform::Component::calculate() {
		// Do nothing
	}

	void Transform::Component::setParent(Component* parent) {
		this->parent = parent;
	}

	Transform::Component* Transform::Component::getParent() {
		return this->parent;
	}

	glm::mat4 Component::resultMatrix() {
		return this->matrix;
	}
}