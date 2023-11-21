#include "scene/entity/BoundingBox.h"
#include "Engine.h"

BoundingBox::BoundingBox(glm::vec3 min, glm::vec3 max) : min(min), max(max) {
	// Empty
}

BoundingBox::~BoundingBox() {
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

glm::vec3 BoundingBox::getMin() const {
	return this->min;
}

glm::vec3 BoundingBox::getMax() const {
	return this->max;
}

bool BoundingBox::intersects(const BoundingBox& other) const {
	return (this->min.x <= other.max.x && this->max.x >= other.min.x) &&
			(this->min.y <= other.max.y && this->max.y >= other.min.y) &&
			(this->min.z <= other.max.z && this->max.z >= other.min.z);
}

bool BoundingBox::isInside(const glm::vec3 point) const {
	return (point.x >= this->min.x && point.x <= this->max.x) &&
			(point.y >= this->min.y && point.y <= this->max.y) &&
			(point.z >= this->min.z && point.z <= this->max.z);
}

void BoundingBox::draw(glm::mat4 modelMatrix) {
	Engine* engine = Engine::getInstance();
	Scene* scene = engine->getSceneHandler()->getActiveScene();

	if (this->shaderProgram == nullptr) {
		this->shaderProgram = engine->getShaderHandler()->createProgram("modelShader.vert", "modelShader.frag");
	}

	if (this->vbo == nullptr) {
		this->vbo = new VBO();
		this->vbo->bind();

		this->points.clear();

		std::vector<glm::vec3> cornerPoints = {
				glm::vec3(min.x, min.y, min.z),
				glm::vec3(max.x, min.y, min.z),
				glm::vec3(min.x, max.y, min.z),
				glm::vec3(max.x, max.y, min.z),
				glm::vec3(min.x, min.y, max.z),
				glm::vec3(max.x, min.y, max.z),
				glm::vec3(min.x, max.y, max.z),
				glm::vec3(max.x, max.y, max.z)
		};

		for (int index : {0, 1, 3, 2, 0, 4, 5, 7, 6, 4, 6, 2, 3, 7, 5, 1}) {
			this->points.emplace_back(cornerPoints[index]);
		}

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
	shaderProgram->setShaderVariable(modelMatrix,"modelMatrix");
	shaderProgram->setShaderVariable(modelMatrix,"normalMatrix");
	shaderProgram->setShaderVariable(scene->getCameraHandler()->getProjectionMatrix(),"projectionMatrix");
	shaderProgram->setShaderVariable(scene->getCameraHandler()->getCamera()->getViewMatrix(),"viewMatrix");

	glDrawArrays(GL_LINE_STRIP, 0, points.size());
}

BoundingBox BoundingBox::get(glm::mat4 matrix) {
	glm::vec3 min = glm::vec3(matrix * glm::vec4(this->min, 1.0f));
	glm::vec3 max = glm::vec3(matrix * glm::vec4(this->max, 1.0f));

	glm::vec3 newMin = glm::vec3(std::min(min.x, max.x), std::min(min.y, max.y), std::min(min.z, max.z));
	glm::vec3 newMax = glm::vec3(std::max(min.x, max.x), std::max(min.y, max.y), std::max(min.z, max.z));

	return BoundingBox(newMin, newMax);
}