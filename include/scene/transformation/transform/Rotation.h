#pragma once

#include "Component.h"

namespace Transform {
	class Rotation : public Component {
		private:
			glm::vec3 rotationVector;

			void calculate() override;
			void innerCalculate(glm::mat4& matrix, glm::vec3 rotationVector);

		public:
			/* -- */ Rotation(float x, float y, float z);
			/* -- */ Rotation(float x, float y, float z, std::function<glm::vec3(glm::vec3)> callback);
			explicit Rotation(glm::vec3 rotationVector);
			/* -- */ Rotation(glm::vec3 rotationVector, std::function<glm::vec3(glm::vec3)> callback);
			/* - */ ~Rotation() override = default;

			glm::vec3 getVector();
	};
}