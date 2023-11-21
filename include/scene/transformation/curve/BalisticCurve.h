#pragma once

#include "scene/transformation/curve/BezierCurve.h"
#include "scene/transformation/transform/Component.h"

namespace Transform {
	class BalisticCurve : public Component {
		private:
			glm::vec3 position;
			glm::vec3 direction;
			float speed = 1.0f;
			glm::vec3 gravity = glm::vec3(0, -0.11, 0);

			void calculate() override;

		public:
			BalisticCurve(glm::vec3 position, glm::vec3 direction, float speed = 1.0f);
			~BalisticCurve() override = default;

			Component* clone() override;
			void draw();
	};
}