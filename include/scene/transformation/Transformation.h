#pragma once

#include "scene/transformation/Transform.h"

class Transformation {
	private:
		Transform::Composite* transform = new Transform::Composite({});

	public:
		/* -- */ Transformation() = default;
		explicit Transformation(Transform::Composite* composite);
		/* - */ ~Transformation();

		void setTransformation(Transform::Composite* composite);
		Transform::Composite* get();

		glm::mat4 resultMatrix();
};