#include "scene/Transformation.h"

namespace Transform {
    Transform::Type Component::getType() const {
        return type;
    }

    void Transform::Component::calculate() {
        // Do nothing
    }

    // ==== | Rotation | ====

    Rotation::Rotation(float x, float y, float z) : Component(Transform::Type::ROTATE), rotationVector(glm::vec3(x, y, z)) {
        calculate();
    }

    Rotation::Rotation(glm::vec3 rotationVector) : Component(Transform::Type::ROTATE), rotationVector(rotationVector) {
        calculate();
    }

    void Transform::Rotation::calculate() {
        rotationVector.x = static_cast<float>(fmod(rotationVector.x, 360.0f));
        rotationVector.y = static_cast<float>(fmod(rotationVector.y, 360.0f));
        rotationVector.z = static_cast<float>(fmod(rotationVector.z, 360.0f));

        matrix = glm::mat4(1.0f);
        matrix = glm::rotate(matrix, glm::radians(rotationVector.x), glm::vec3(1.0f, 0.0f, 0.0f));
        matrix = glm::rotate(matrix, glm::radians(rotationVector.y), glm::vec3(0.0f, 1.0f, 0.0f));
        matrix = glm::rotate(matrix, glm::radians(rotationVector.z), glm::vec3(0.0f, 0.0f, 1.0f));
    }

    glm::vec3 Transform::Rotation::getVector() {
        return this->rotationVector;
    }

    glm::mat4 Transform::Rotation::resultMatrix() const {
        return this->matrix;
    }

    // ==== | Translate | ====

    Translate::Translate(float x, float y, float z) : Component(Transform::Type::TRANSLATE), translationVector(glm::vec3(x, y, z)) {
        calculate();
    }

    Translate::Translate(glm::vec3 translationVector) : Component(Transform::Type::TRANSLATE), translationVector(translationVector) {
        calculate();
    }

    void Translate::calculate() {
        matrix = glm::mat4(1.0f);
        matrix = glm::translate(matrix, glm::vec3(translationVector.x, translationVector.y, translationVector.z));
    }

    glm::vec3 Translate::getVector() {
        return this->translationVector;
    }

    glm::mat4 Translate::resultMatrix() const {
        return this->matrix;
    }

    // ==== | Scale | ====

    Scale::Scale(float scale) : Component(Transform::Type::SCALE), scaleVector(glm::vec3(scale, scale, scale)) {
        calculate();
    }

    Scale::Scale(glm::vec3 scaleVector) : Component(Transform::Type::SCALE), scaleVector(scaleVector) {
        calculate();
    }

    Scale::Scale(float x, float y, float z) : Component(Transform::Type::SCALE), scaleVector(glm::vec3(x, y, z)) {
        calculate();
    }

    void Scale::calculate() {
        scaleVector.x = float(fmax(scaleVector.x, 0.1f));
        scaleVector.y = float(fmax(scaleVector.y, 0.1f));
        scaleVector.z = float(fmax(scaleVector.z, 0.1f));

        matrix = glm::mat4(1.0f);
        matrix = glm::scale(matrix, glm::vec3(scaleVector.x, scaleVector.y, scaleVector.z));
    }

    glm::vec3 Scale::getVector() {
        return this->scaleVector;
    }

    glm::mat4 Scale::resultMatrix() const {
        return this->matrix;
    }

    // ==== | Composite | ====

    Composite::Composite(const std::vector<Component*> &transforms) : Component(Transform::Type::COMPOSITE), transforms(transforms) {
        calculate();
    }

	Composite::~Composite() {
		for (const auto &transform: this->transforms) {
			delete transform;
		}
	}

    void Composite::calculate() {
	    this->matrix = glm::mat4(1.0f);

        for (const auto &transform: transforms) {
	        this->matrix = this->matrix * transform->resultMatrix();
        }
    }

    glm::mat4 Composite::resultMatrix() const {
        return this->matrix;
    }

    std::vector<Component*>& Composite::get() {
        return this->transforms;
    }

    bool Composite::isEmpty() {
        return this->transforms.empty();
    }
};

// ==== | Transformation | ====

Transformation::Transformation() {
    this->transform = new Transform::Composite({});
}

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