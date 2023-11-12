#include <glm/ext/matrix_transform.hpp>
#include "scene/transformation/transform/Translate.h"

namespace Transform {
	void Translate::innerCalculate(glm::mat4& matrix, glm::vec3 translationVector) {
		matrix = glm::mat4(1.0f);
		matrix = glm::translate(matrix, glm::vec3(translationVector.x, translationVector.y, translationVector.z));
	}

	Translate::Translate(float x, float y, float z) : Component(Transform::Type::TRANSLATE, nullptr) {
		this->translationVector = glm::vec3(x, y, z);
		innerCalculate(this->matrix, this->translationVector);
	}

	Translate::Translate(float x, float y, float z, std::function<glm::vec3(glm::vec3)> callback) : Component(Transform::Type::TRANSLATE, callback) {
		this->translationVector = glm::vec3(x, y, z);
		innerCalculate(this->matrix, this->translationVector);
	}

	Translate::Translate(glm::vec3 translationVector) : Component(Transform::Type::TRANSLATE, nullptr) {
		this->translationVector = translationVector;
		innerCalculate(this->matrix, this->translationVector);
	}

	Translate::Translate(glm::vec3 translationVector, std::function<glm::vec3(glm::vec3)> callback) : Component(Transform::Type::TRANSLATE, callback) {
		this->translationVector = translationVector;
		innerCalculate(this->matrix, this->translationVector);
	}

	void Translate::calculate() {
		if (this->callback != nullptr) {
			this->translationVector = this->callback(this->translationVector);
			innerCalculate(this->matrix, this->translationVector);
		}
	}

	glm::vec3 Translate::getVector() {
		return this->translationVector;
	}
}