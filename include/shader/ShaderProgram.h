#pragma once

#include "Shader.h"

#include <variant>
#include <vector>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

class AbstractLight;
class ShaderProgram {
	private:
		std::string name;

		std::vector<Shader*> shaders;
		GLuint program;

	public:
		ShaderProgram(const std::string &name);
		~ShaderProgram();

		void attach(Shader* shader);

		void setShaderVariable(const glm::mat2 &mat, const std::string &variable);
		void setShaderVariable(const glm::mat3 &mat, const std::string &variable);
		void setShaderVariable(const glm::mat4 &mat, const std::string &variable);
		void setShaderVariable(const glm::vec2 &vec, const std::string &variable);
		void setShaderVariable(const glm::vec3 &vec, const std::string &variable);
		void setShaderVariable(const glm::vec4 &vec, const std::string &variable);
		void setShaderVariable(int value, const std::string &variable);
		void setShaderVariable(bool state, const std::string &variable);
		void setShaderVariable(float value, const std::string &variable);
		void setShaderLight(AbstractLight* light);

		void link();
		void use();
		void unUse();

		std::string toString();
};
