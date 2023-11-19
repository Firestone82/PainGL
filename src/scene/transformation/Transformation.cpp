#include "scene/transformation/Transformation.h"

Transformation::Transformation(Transform::Composite* composite) {
	this->transform = composite;
}

Transformation::~Transformation() {
	delete this->transform;
}

Transformation& Transformation::operator= (const Transformation& other) {
	if (this != &other) {
		delete this->transform;
		this->transform = other.transform;
	}

	return *this;
}

void Transformation::setTransformation(Transform::Composite* composite) {
	delete this->transform;
	this->transform = composite;
}

glm::mat4 Transformation::resultMatrix() {
	return this->transform->resultMatrix();
}

void Transformation::calculate() {
	this->transform->calculate();
}

Transform::Composite* Transformation::get() {
	return this->transform;
}

Transform::Composite* Transformation::clone() {
	return dynamic_cast<Transform::Composite *>(this->transform->clone());
}