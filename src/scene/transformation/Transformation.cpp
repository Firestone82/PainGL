#include "scene/transformation/Transformation.h"

Transformation::Transformation(Transform::Composite* composite) {
	this->transform = composite;
}

Transformation::~Transformation() {
	delete this->transform;
}

void Transformation::setTransformation(Transform::Composite* composite) {
	delete this->transform;
	this->transform = composite;
}

glm::mat4 Transformation::resultMatrix() {
	return this->transform->resultMatrix();
}

Transform::Composite* Transformation::get() {
	return this->transform;
}