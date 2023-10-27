#include <stdexcept>
#include <variant>
#include "shader/ShaderProgram.h"
#include "utils/Logger.h"
#include "Engine.h"
#include "event/type/CameraEvents.h"
#include "event/type/SceneEvents.h"

ShaderProgram::ShaderProgram(const std::string &name) : name(name) {
	this->program = glCreateProgram();

	// Listener for camera zoom
	Engine::getInstance()->getEventHandler()->addListener(new Listener<CameraZoomEvent>([=](CameraZoomEvent* event) {
		this->use();
		this->setShaderVariableMatrix(event->getCameraHandler()->getProjectionMatrix(), "projectionMatrix");
	}));

	// Listener for camera rotation
	Engine::getInstance()->getEventHandler()->addListener(new Listener<CameraRotateEvent>([=](CameraRotateEvent* event) {
		this->use();
		this->setShaderVariableMatrix(event->getCamera()->getViewMatrix(), "viewMatrix");
	}));

	// Listener for camera movement
	Engine::getInstance()->getEventHandler()->addListener(new Listener<CameraMoveEvent>([=](CameraMoveEvent* event) {
		this->use();
		this->setShaderVariableMatrix(event->getCamera()->getViewMatrix(), "viewMatrix");
		this->setShaderVariableVector(event->getCamera()->getPosition(), "camera.position");
	}));

	// Listener for switching scenes
	Engine::getInstance()->getEventHandler()->addListener(new Listener<SceneSwitchEvent>([=](SceneSwitchEvent* event) {
		this->use();
		this->setShaderVariableMatrix(event->getNewScene()->getCameraHandler()->getCamera()->getViewMatrix(), "viewMatrix");
		this->setShaderVariableMatrix(event->getNewScene()->getCameraHandler()->getProjectionMatrix(), "projectionMatrix");
		this->setShaderVariableVector(event->getNewScene()->getCameraHandler()->getCamera()->getPosition(), "camera.position");

		this->setShaderVariableInt(event->getNewScene()->getLightHandler()->getLights().size(), "numLights");
		for (Light* light: event->getNewScene()->getLightHandler()->getLights()){
			light->calculateTransformationMatrix();
			this->setShaderVariableVector(light->getPosition(), "lights["+ std::to_string(light->getID())  +"].position");
			this->setShaderVariableVector(light->getColor(), "lights["+ std::to_string(light->getID()) +"].color");
		}
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

static long lastNotify = 0;
void ShaderProgram::setShaderVariableMatrix(const std::variant<glm::mat2, glm::mat3, glm::mat4> &matrix, const std::string &variable) {
	GLint uniformLocation = glGetUniformLocation(this->program, variable.c_str());

	if (uniformLocation == -1) {
		if (lastNotify + 1000 < glfwGetTime()) {
			Logger::warning(R"(ShaderProgram "%s": Uniform variable "%s" not found)", this->name.c_str(), variable.c_str());
			lastNotify = glfwGetTime();
		}

		return;
	}

	if (std::holds_alternative<glm::mat2>(matrix)) {
		glUniformMatrix2fv(uniformLocation, 1, GL_FALSE, glm::value_ptr(std::get<glm::mat2>(matrix)));
	} else if (std::holds_alternative<glm::mat3>(matrix)) {
		glUniformMatrix3fv(uniformLocation, 1, GL_FALSE, glm::value_ptr(std::get<glm::mat3>(matrix)));
	} else {
		glUniformMatrix4fv(uniformLocation, 1, GL_FALSE, glm::value_ptr(std::get<glm::mat4>(matrix)));
	}
}

void ShaderProgram::setShaderVariableVector(const std::variant<glm::vec2, glm::vec3, glm::vec4> &vector, const std::string &variable) {
	GLint uniformLocation = glGetUniformLocation(this->program, variable.c_str());

	if (uniformLocation == -1) {
		if (lastNotify + 1000 < glfwGetTime()) {
			Logger::warning(R"(ShaderProgram "%s": Uniform variable "%s" not found)", this->name.c_str(), variable.c_str());
			lastNotify = glfwGetTime();
		}

		return;
	}

	if (std::holds_alternative<glm::vec2>(vector)) {
		glUniform2fv(uniformLocation, 1, glm::value_ptr(std::get<glm::vec2>(vector)));
	} else if (std::holds_alternative<glm::vec3>(vector)) {
		glUniform3fv(uniformLocation, 1, glm::value_ptr(std::get<glm::vec3>(vector)));
	} else {
		glUniform4fv(uniformLocation, 1, glm::value_ptr(std::get<glm::vec4>(vector)));
	}
}

void ShaderProgram::setShaderVariableInt(int value, const std::string &variable) {
	GLint uniformLocation = glGetUniformLocation(this->program, variable.c_str());
	glUniform1i(uniformLocation, value);
}

void ShaderProgram::setShaderVariableFloat(float value, const std::string &variable) {
	GLint uniformLocation = glGetUniformLocation(this->program, variable.c_str());
	glUniform1f(uniformLocation, value);
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

void ShaderProgram::update() {
	this->use();
	this->setShaderVariableMatrix(Engine::getInstance()->getSceneHandler()->getActiveScene()->getCameraHandler()->getProjectionMatrix(), "projectionMatrix");
	this->setShaderVariableMatrix(Engine::getInstance()->getSceneHandler()->getActiveScene()->getCameraHandler()->getCamera()->getViewMatrix(), "viewMatrix");
}

void ShaderProgram::unset() {
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