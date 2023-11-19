#pragma once

#include "Component.h"

namespace Transform {
	class Translate : public Component {
		protected:
			glm::vec3 translationVector;

			void calculate() override;
			void innerCalculate(glm::mat4& matrix, glm::vec3 translationVector);

		public:
			/* -- */ Translate(float x, float y, float z);
			/* -- */ Translate(float x, float y, float z, std::function<glm::vec3(glm::vec3)> callback);
			explicit Translate(glm::vec3 translationVector);
			/* -- */ Translate(glm::vec3 translationVector, std::function<glm::vec3(glm::vec3)> callback);
			/* - */ ~Translate() override = default;

			glm::vec3 getVector();
			Component* clone() override;
	};
}