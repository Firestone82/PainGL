#include "shader/Shader.h"
#include "utils/Logger.h"

Shader::Shader(const std::string &name, GLenum type, const char *source) : name(name), source(source) {
	this->shader = glCreateShader(type);
	glShaderSource(this->shader, 1, &this->source, nullptr);
	glCompileShader(this->shader);

	GLint status;
	glGetShaderiv(this->shader, GL_COMPILE_STATUS, &status);

	// Check if shader compiled successfully
	if (status == GL_FALSE) {
		GLint infoLogLength;
		glGetShaderiv(this->shader, GL_INFO_LOG_LENGTH, &infoLogLength);

		auto *infoLog = new GLchar[infoLogLength + 1];
		glGetShaderInfoLog(this->shader, infoLogLength, nullptr, infoLog);

		Logger::error("Shader compilation failed: %s", infoLog);
		delete[] infoLog;
	}
}

Shader::~Shader() {
	glDeleteShader(this->shader);
}

std::string Shader::getName() const {
	return this->name;
}

GLenum Shader::get() const {
	return this->shader;
}