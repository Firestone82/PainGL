#include <stdexcept>
#include <variant>

#include "shader/ShaderProgram.h"
#include "event/type/CameraEvents.h"
#include "event/type/SceneEvents.h"
#include "event/type/LightEvents.h"
#include "utils/Logger.h"
#include "Engine.h"

ShaderProgram::ShaderProgram(const std::string &name) : name(name) {
	this->program = glCreateProgram();

	// Listener for camera zoom
	Engine::getInstance()->getEventHandler()->addListener(new Listener<CameraZoomEvent>([=](CameraZoomEvent* event) {
		this->use();
		this->setShaderVariable(event->getCameraHandler()->getProjectionMatrix(), "projectionMatrix");
	}));

	// Listener for camera rotation
	Engine::getInstance()->getEventHandler()->addListener(new Listener<CameraRotateEvent>([=](CameraRotateEvent* event) {
		this->use();
		this->setShaderVariable(event->getCamera()->getViewMatrix(), "viewMatrix");
	}));

	// Listener for camera movement
	Engine::getInstance()->getEventHandler()->addListener(new Listener<CameraMoveEvent>([=](CameraMoveEvent* event) {
		this->use();
		this->setShaderVariable(event->getCamera()->getViewMatrix(), "viewMatrix");
		this->setShaderVariable(event->getCamera()->getPosition(), "camera.position");
	}));

	// Listener for light update
	Engine::getInstance()->getEventHandler()->addListener(new Listener<LightUpdateEvent>([=](LightUpdateEvent* event) {
		this->use();
		this->setShaderLight(event->getLight());
	}));
}

ShaderProgram::~ShaderProgram() {
	for (const auto &shader: this->shaders) {
		glDetachShader(this->program, shader->get());
		this->shaders.pop_back();
	}

	glDeleteProgram(this->program);
}

void ShaderProgram::attach(Shader* shader) {
	this->shaders.push_back(shader);
	glAttachShader(this->program, shader->get());
}

static long lastNotify = glfwGetTime();
void notify(const std::string message, ...) {
//	if (lastNotify + 10 < glfwGetTime()) {
//		va_list args;
//		va_start(args, message);
//		Logger::warning(message, args);
//		printf(message.c_str(), args);
//		va_end(args);
//
//		lastNotify = glfwGetTime();
//	}
}

void ShaderProgram::setShaderVariable(const glm::mat2 &mat, const std::string &variable) {
	GLint uniformLocation = glGetUniformLocation(this->program, variable.c_str());

	if (uniformLocation == -1) {
		notify(R"(ShaderProgram "%s": Uniform variable "%s" not found)", this->name.c_str(), variable.c_str());
		return;
	}

	glUniformMatrix2fv(uniformLocation, 1, GL_FALSE, glm::value_ptr(mat));
}

void ShaderProgram::setShaderVariable(const glm::mat3 &mat, const std::string &variable) {
	GLint uniformLocation = glGetUniformLocation(this->program, variable.c_str());

	if (uniformLocation == -1) {
		notify(R"(ShaderProgram "%s": Uniform variable "%s" not found)", this->name.c_str(), variable.c_str());
		return;
	}

	glUniformMatrix3fv(uniformLocation, 1, GL_FALSE, glm::value_ptr(mat));
}

void ShaderProgram::setShaderVariable(const glm::mat4 &mat, const std::string &variable) {
	GLint uniformLocation = glGetUniformLocation(this->program, variable.c_str());

	if (uniformLocation == -1) {
		notify(R"(ShaderProgram "%s": Uniform variable "%s" not found)", this->name.c_str(), variable.c_str());
		return;
	}

	glUniformMatrix4fv(uniformLocation, 1, GL_FALSE, glm::value_ptr(mat));
}

void ShaderProgram::setShaderVariable(const glm::vec2 &mat, const std::string &variable) {
	GLint uniformLocation = glGetUniformLocation(this->program, variable.c_str());

	if (uniformLocation == -1) {
		notify(R"(ShaderProgram "%s": Uniform variable "%s" not found)", this->name.c_str(), variable.c_str());
		return;
	}

	glUniform2fv(uniformLocation, 1, glm::value_ptr(mat));
}

void ShaderProgram::setShaderVariable(const glm::vec3 &mat, const std::string &variable) {
	GLint uniformLocation = glGetUniformLocation(this->program, variable.c_str());

	if (uniformLocation == -1) {
		notify(R"(ShaderProgram "%s": Uniform variable "%s" not found)", this->name.c_str(), variable.c_str());
		return;
	}

	glUniform3fv(uniformLocation, 1, glm::value_ptr(mat));
}

void ShaderProgram::setShaderVariable(const glm::vec4 &mat, const std::string &variable) {
	GLint uniformLocation = glGetUniformLocation(this->program, variable.c_str());

	if (uniformLocation == -1) {
		notify(R"(ShaderProgram "%s": Uniform variable "%s" not found)", this->name.c_str(), variable.c_str());
		return;
	}

	glUniform4fv(uniformLocation, 1, glm::value_ptr(mat));
}

void ShaderProgram::setShaderVariable(int value, const std::string &variable) {
	GLint uniformLocation = glGetUniformLocation(this->program, variable.c_str());

	if (uniformLocation == -1) {
		notify(R"(ShaderProgram "%s": Uniform variable "%s" not found)", this->name.c_str(), variable.c_str());
		return;
	}

	glUniform1i(uniformLocation, value);
}

void ShaderProgram::setShaderVariable(bool state, const std::string &variable) {
	GLint uniformLocation = glGetUniformLocation(this->program, variable.c_str());

	if (uniformLocation == -1) {
		notify(R"(ShaderProgram "%s": Uniform variable "%s" not found)", this->name.c_str(), variable.c_str());
		return;
	}

	glUniform1i(uniformLocation, state);
}

void ShaderProgram::setShaderVariable(float value, const std::string &variable) {
	GLint uniformLocation = glGetUniformLocation(this->program, variable.c_str());

	if (uniformLocation == -1) {
		notify(R"(ShaderProgram "%s": Uniform variable "%s" not found)", this->name.c_str(), variable.c_str());
		return;
	}

	glUniform1f(uniformLocation, value);
}

void ShaderProgram::setShaderLight(AbstractLight* light) {
	std::string id = std::to_string(light->getID());
	std::string prefix = "lights[" + id + "].";

	this->setShaderVariable(int(light->getType()), prefix + "type");

	for (const auto &[key, value]: light->getShaderVariables()) {
		if (std::holds_alternative<glm::vec3>(value)) {
			this->setShaderVariable(std::get<glm::vec3>(value), prefix + key);
		} else if (std::holds_alternative<float>(value)) {
			this->setShaderVariable(std::get<float>(value), prefix + key);
		} else {
			Logger::warning("ShaderProgram: Unknown shader variable type");
		}
	}
}

void ShaderProgram::link() {
	glLinkProgram(this->program);

	GLint status;
	glGetProgramiv(this->program, GL_LINK_STATUS, &status);

	// Check if program linked successfully
	if (status == GL_FALSE) {
		GLint infoLogLength;
		glGetProgramiv(this->program, GL_INFO_LOG_LENGTH, &infoLogLength);

		auto *strInfoLog = new GLchar[infoLogLength + 1];
		glGetProgramInfoLog(this->program, infoLogLength, nullptr, strInfoLog);

		Logger::error("ShaderProgram linking failure: %s", strInfoLog);
		delete[] strInfoLog;
		throw std::runtime_error("ShaderProgram linking failure");
	}
}

void ShaderProgram::use() {
	glUseProgram(this->program);
}

void ShaderProgram::unUse() {
	glUseProgram(0);
}

std::string ShaderProgram::toString() {
	std::string result;

	for (const auto &shader: this->shaders) {
		result += shader->getName() + ", ";
	}

	// Remove trailing comma
	std::string::size_type pos = result.find_last_of(',');
	if (pos != std::string::npos) {
		result.erase(pos, 1);
	}

	return result;
}
