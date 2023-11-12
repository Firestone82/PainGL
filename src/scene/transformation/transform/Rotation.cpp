#include "scene/transformation/transform/Rotation.h"

#include <glm/ext/matrix_transform.hpp>

namespace Transform {
	void Rotation::innerCalculate(glm::mat4& matrix, glm::vec3 rotationVector) {
		matrix = glm::mat4(1.0f);

		rotationVector.x = float(fmod(rotationVector.x, 360.0f));
		rotationVector.y = float(fmod(rotationVector.y, 360.0f));
		rotationVector.z = float(fmod(rotationVector.z, 360.0f));

		matrix = glm::rotate(matrix, glm::radians(rotationVector.x), glm::vec3(1.0f, 0.0f, 0.0f));
		matrix = glm::rotate(matrix, glm::radians(rotationVector.y), glm::vec3(0.0f, 1.0f, 0.0f));
		matrix = glm::rotate(matrix, glm::radians(rotationVector.z), glm::vec3(0.0f, 0.0f, 1.0f));
	}

	Rotation::Rotation(float x, float y, float z) : Component(Transform::Type::ROTATE, nullptr) {
		this->rotationVector = glm::vec3(x, y, z);
		innerCalculate(this->matrix, this->rotationVector);
	}

	Rotation::Rotation(float x, float y, float z, std::function<glm::vec3(glm::vec3)> callback) : Component(Transform::Type::ROTATE, callback) {
		this->rotationVector = glm::vec3(x, y, z);
		innerCalculate(this->matrix, this->rotationVector);
	}

	Rotation::Rotation(glm::vec3 rotationVector) : Component(Transform::Type::ROTATE, nullptr) {
		this->rotationVector = rotationVector;
		innerCalculate(this->matrix, this->rotationVector);
	}

	Rotation::Rotation(glm::vec3 rotationVector, std::function<glm::vec3(glm::vec3)> callback) : Component(Transform::Type::ROTATE, callback) {
		this->rotationVector = rotationVector;
		innerCalculate(this->matrix, this->rotationVector);
	}

	void Rotation::calculate() {
		if (this->callback != nullptr) {
			this->rotationVector = this->callback(this->rotationVector);
			innerCalculate(this->matrix, this->rotationVector);
		}
	}

	glm::vec3 Rotation::getVector() {
		return this->rotationVector;
	}
}