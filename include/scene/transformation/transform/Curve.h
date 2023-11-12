#pragma once

#include "scene/transformation/curve/BezierCurve.h"
#include "Component.h"

namespace Transform {
	class Curve : public Component {
		private:
			BezierCurve* curve = nullptr;
			float precision;
			float speed;

			void calculate() override;

		public:
			Curve(std::vector<glm::vec3> points, float precision);
			Curve(std::vector<glm::vec3> points, float precision, float speed);
			~Curve() override = default;

			BezierCurve& getCurve();
	};
}