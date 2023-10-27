#pragma once

#include "Shader.h"

#include <variant>
#include <vector>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

class ShaderProgram {
	private:
		std::string name;

		std::vector<Shader*> shaders;
		GLuint program;

	public:
		ShaderProgram(const std::string &name);
		~ShaderProgram();

		void attach(Shader* shader);
		void setShaderVariableMatrix(const std::variant<glm::mat2, glm::mat3, glm::mat4> &matrix, const std::string &variable);
		void setShaderVariableVector(const std::variant<glm::vec2, glm::vec3, glm::vec4> &vector, const std::string &variable);
		void setShaderVariableInt(int integer, const std::string &variable);
		void setShaderVariableFloat(float value, const std::string &variable);

		void link();
		void use();
		void update();
		void unset();

		std::string toString();
};
