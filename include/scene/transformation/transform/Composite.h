#pragma once

#include "Component.h"

#include <vector>
#include <glm/glm.hpp>

namespace Transform {
	class Composite : public Component {
		private:
			std::vector<Component*> transforms;

			void innerCalculate(glm::mat4& matrix, const std::vector<Component*>& transforms);

		public:
			explicit Composite(const std::vector<Component*> &transforms);
			/* - */ ~Composite() override;

			std::vector<Component*>& get();
			glm::mat4 resultMatrix() override;

			bool isEmpty();
			void calculate() override;
	};
};
