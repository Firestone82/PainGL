#pragma once

#include "Component.h"

namespace Transform {
	class Scale : public Component {
		private:
			glm::vec3 scaleVector;

			void calculate() override;
			void innerCalculate(glm::mat4& matrix, glm::vec3 scaleVector);

		public:
			explicit Scale(float scale);
			/* -- */ Scale(float scale, std::function<glm::vec3(glm::vec3)> callback);
			explicit Scale(glm::vec3 scaleVector);
			/* -- */ Scale(glm::vec3 scaleVector, std::function<glm::vec3(glm::vec3)> callback);
			/* -- */ Scale(float x, float y, float z);
			/* -- */ Scale(float x, float y, float z, std::function<glm::vec3(glm::vec3)> callback);
			/* - */ ~Scale() override = default;

			glm::vec3 getVector();
			Component* clone() override;
	};
}