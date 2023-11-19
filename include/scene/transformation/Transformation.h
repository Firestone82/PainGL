#pragma once

#include "scene/transformation/transform/Composite.h"

class Transformation {
	private:
		Transform::Composite* transform = new Transform::Composite({});

	public:
		/* -- */ Transformation() = default;
		explicit Transformation(Transform::Composite* composite);
		/* - */ ~Transformation();
		Transformation& operator= (const Transformation& other);

		void setTransformation(Transform::Composite* composite);
		Transform::Composite* get();
		Transform::Composite* clone();

		glm::mat4 resultMatrix();
		void calculate();
};