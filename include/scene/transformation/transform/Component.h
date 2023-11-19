#pragma once

#include <glm/vec3.hpp>
#include <glm/mat4x4.hpp>
#include <functional>
#include <vector>

namespace Transform {
	enum Type {
		COMPOSITE,
		TRANSLATE,
		ROTATE,
		SCALE,
		CURVE,
	};

	class Component {
		protected:
			glm::mat4 matrix = glm::mat4(1.0f);
			Component* parent = nullptr;
			Transform::Type type;

			std::function<glm::vec3(glm::vec3)> callback = nullptr;

		public:
			explicit Component(Transform::Type type, std::function<glm::vec3(glm::vec3)> call);
			virtual ~Component() = default;

			virtual void calculate() = 0;
			Transform::Type getType() const;

			void setParent(Component* parent);
			Component* getParent();

			virtual glm::mat4 resultMatrix();
			virtual Component* clone() = 0;
	};
};
