#pragma once

#include "scene/transformation/curve/BezierCurve.h"
#include "Component.h"

namespace Transform {
	class Curve : public Component {
		private:
			std::vector<BezierCurve*> curves;
			float speed = 1.0f;

			void calculate() override;

		public:
			Curve(std::vector<BezierCurve> points, float speed = 1.0f);
			~Curve() override = default;

			Component* clone() override;
	};
}