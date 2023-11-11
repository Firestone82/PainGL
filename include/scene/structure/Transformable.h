#pragma once

#include "scene/transformation/Transformation.h"

#include <glm/glm.hpp>
#include <glm/mat4x4.hpp>

class Transformable {
	protected:
		Transformation* transformation = new Transformation();
		glm::mat4 matrix = glm::mat4(1.0f);

	public:
		Transformable() = default;
		~Transformable() {
			delete this->transformation;
		}

		Transformation* getTransformation() {
			return this->transformation;
		}

		glm::mat4 getTransformationMatrix() const {
			return this->matrix;
		}

		void calculateTransformationMatrix() {
			this->matrix = this->transformation->resultMatrix();
		}

		glm::vec3 getPosition() const {
			glm::mat4 mat = getTransformationMatrix();

			return {mat[3][0], mat[3][1], mat[3][2]};
		}

		glm::vec3 getRotation() {
			glm::mat4 mat = getTransformationMatrix();

			auto x = static_cast<float>(atan2(mat[2][1], mat[2][2]));
			auto y = static_cast<float>(atan2(mat[2][0], sqrt(pow(mat[2][1], 2) + pow(mat[2][2], 2))));
			auto z = static_cast<float>(atan2(mat[1][0], mat[0][0]));

			return {glm::degrees(x), glm::degrees(y), glm::degrees(z)};
		}

		glm::vec3 getScale() {
			glm::mat4 mat = getTransformationMatrix();

			auto x = static_cast<float>(sqrt(pow(mat[0][0], 2) + pow(mat[0][1], 2) + pow(mat[0][2], 2)));
			auto y = static_cast<float>(sqrt(pow(mat[1][0], 2) + pow(mat[1][1], 2) + pow(mat[1][2], 2)));
			auto z = static_cast<float>(sqrt(pow(mat[2][0], 2) + pow(mat[2][1], 2) + pow(mat[2][2], 2)));

			return {x, y, z};
		}
};