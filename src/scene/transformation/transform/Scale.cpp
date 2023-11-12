#include "scene/transformation/transform/Scale.h"
#include "utils/Logger.h"

#include <glm/ext/matrix_transform.hpp>

namespace Transform {
	void Scale::innerCalculate(glm::mat4& matrix, glm::vec3 scaleVector) {
		matrix = glm::mat4(1.0f);

		scaleVector.x = float(fmax(scaleVector.x, 0.1f));
		scaleVector.y = float(fmax(scaleVector.y, 0.1f));
		scaleVector.z = float(fmax(scaleVector.z, 0.1f));

		matrix = glm::scale(matrix, glm::vec3(scaleVector.x, scaleVector.y, scaleVector.z));
	}

	Scale::Scale(float scale) : Component(Transform::Type::SCALE, nullptr) {
		this->scaleVector = glm::vec3(scale);
		innerCalculate(this->matrix, this->scaleVector);
	}

	Scale::Scale(float scale, std::function<glm::vec3(glm::vec3)> callback) : Component(Transform::Type::SCALE, callback) {
		this->scaleVector = glm::vec3(scale);
		innerCalculate(this->matrix, this->scaleVector);
	}

	Scale::Scale(glm::vec3 scaleVector) : Component(Transform::Type::SCALE, nullptr) {
		this->scaleVector = scaleVector;
		innerCalculate(this->matrix, this->scaleVector);
	}

	Scale::Scale(glm::vec3 scaleVector, std::function<glm::vec3(glm::vec3)> callback) : Component(Transform::Type::SCALE, callback) {
		this->scaleVector = scaleVector;
		innerCalculate(this->matrix, this->scaleVector);
	}

	Scale::Scale(float x, float y, float z) : Component(Transform::Type::SCALE, nullptr) {
		this->scaleVector = glm::vec3(x, y, z);
		innerCalculate(this->matrix, this->scaleVector);
	}

	Scale::Scale(float x, float y, float z, std::function<glm::vec3(glm::vec3)> callback) : Component(Transform::Type::SCALE, callback) {
		this->scaleVector = glm::vec3(x, y, z);
		innerCalculate(this->matrix, this->scaleVector);
	}

	void Scale::calculate() {
		if (this->callback != nullptr) {
			this->scaleVector = this->callback(this->scaleVector);
			innerCalculate(this->matrix, this->scaleVector);
		}
	}

	glm::vec3 Scale::getVector() {
		return this->scaleVector;
	}
}