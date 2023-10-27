#pragma once

#include "scene/structure/Object.h"
#include "shader/ShaderProgram.h"
#include "model/Model.h"

class Light : public Object<Light> {
	private:
		glm::vec3 color = glm::vec3(1.0f, 1.0f, 1.0f);

		explicit Light(const std::string &name) : Object(name) {};

	public:
		~Light() override;

		void draw() override;

		void setColor(glm::vec3 rgb);
		glm::vec3 getColor() const;

	class Builder {
		private:
			Light* light;

		public:
			explicit Builder(const std::string &name);

			Builder* setColor(glm::vec3 color);
			Builder* setTransformation(Transform::Composite* composite);
			Builder* setSimulateFunction(const std::function<void(Light*, float)>& simulateFunction);

			Light* build();
	};

	static Builder* createLight(const std::string &name);
};
