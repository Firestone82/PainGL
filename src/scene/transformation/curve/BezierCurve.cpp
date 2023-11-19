#include "scene/transformation/curve/BezierCurve.h"
#include "utils/Logger.h"
#include "Engine.h"

#include <math.h>
#include <GL/glew.h>

BezierCurve::BezierCurve(std::initializer_list<glm::vec3> points) : controlPoints(points) {
	// Empty
}

BezierCurve::~BezierCurve() {
	if (this->vao != nullptr) {
		delete this->vao;
		this->vao = nullptr;
	}

	if (this->vbo != nullptr) {
		delete this->vbo;
		this->vbo = nullptr;
	}

	this->shaderProgram = nullptr;
}

float binomialCoefficient(int n, int k) {
	float result = 1.0f;

	for (int i = 1; i <= k; i++) {
		result *= (float) (n - i + 1) / (float) i;
	}

	return result;
}

glm::vec3 BezierCurve::getPoint(float t) const {
	glm::vec3 point = glm::vec3(0.0f, 0.0f, 0.0f);

	for (int j = 0; j < controlPoints.size(); j++) {
		float binomial = binomialCoefficient(controlPoints.size() - 1, j);
		float power1 = pow(1 - t, controlPoints.size() - 1 - j);
		float power2 = pow(t, j);

		point += binomial * power1 * power2 * controlPoints[j];
	}

	return point;
}

std::vector<glm::vec3> BezierCurve::getControlPoints() const {
	return controlPoints;
}

void BezierCurve::draw() {
	Engine* engine = Engine::getInstance();
	Scene* scene = engine->getSceneHandler()->getActiveScene();

	if (this->shaderProgram == nullptr) {
		this->shaderProgram = engine->getShaderHandler()->createProgram("modelShader.vert", "modelShader.frag");
	}

	if (this->vbo == nullptr) {
		this->vbo = new VBO();
		this->vbo->bind();

		for (float t = 0.0f; t <= 1.0f; t += 0.1f) {
			points.push_back(this->getPoint(t));
		}
		points.push_back(this->getPoint(1.0f));

		this->vbo->setData(&points[0], points.size() * sizeof(glm::vec3), GL_STATIC_DRAW);
	} else {
		this->vbo->bind();
	}

	if (this->vao == nullptr) {
		this->vao = new VAO();
		this->vao->bind();

		this->vao->setEnableVertexArray(0);
		this->vao->setVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, nullptr);
	} else {
		this->vao->bind();
	}

	shaderProgram->use();
	shaderProgram->setShaderVariable(glm::mat4(1.0f),"modelMatrix");
	shaderProgram->setShaderVariable(glm::mat4(1.0f),"normalMatrix");
	shaderProgram->setShaderVariable(scene->getCameraHandler()->getProjectionMatrix(),"projectionMatrix");
	shaderProgram->setShaderVariable(scene->getCameraHandler()->getCamera()->getViewMatrix(),"viewMatrix");

	glDrawArrays(GL_LINE_STRIP, 0, points.size());
}