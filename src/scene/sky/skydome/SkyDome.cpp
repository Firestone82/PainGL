#include "utils/Logger.h"
#include "model/Model.h"
#include "Engine.h"
#include "scene/sky/skydome/SkyDome.h"

SkyDome::SkyDome(const std::string &name, Path* image) : Sky(name) {
	this->id = 0;
	this->model = Engine::getInstance()->getModelHandler()->getModel("dome");
	this->shaderProgram = Engine::getInstance()->getShaderHandler()->createProgram("skydome.vert", "skydome.frag");
	this->image = image;

	this->init();
}

SkyDome::~SkyDome() {
	this->model = nullptr;
	this->shaderProgram = nullptr;
	delete this->image;

	glDeleteTextures(1, &this->texture);
	this->texture = 0;
}

void SkyDome::init() {
	this->texture = 0;
	glGenTextures(1, &this->texture);
	glBindTexture(GL_TEXTURE_2D, this->texture);

	Image* loadedImage = new Image(*this->image);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, loadedImage->getWidth(), loadedImage->getHeight(), 0, GL_RGB, GL_UNSIGNED_BYTE, loadedImage->getData());
	glGenerateMipmap(GL_TEXTURE_2D);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

	delete loadedImage;
}

void SkyDome::draw() {
	glDepthMask(GL_FALSE);

	Scene* scene = Engine::getInstance()->getSceneHandler()->getActiveScene();
	glm::mat4 viewMatrix = glm::mat4(glm::mat3(scene->getCameraHandler()->getCamera()->getViewMatrix()));
	glm::mat4 projectionMatrix = scene->getCameraHandler()->getProjectionMatrix();

	this->shaderProgram->use();
	this->shaderProgram->setShaderVariable(0,"skyTexture");
	this->shaderProgram->setShaderVariable(viewMatrix,"viewMatrix");
	this->shaderProgram->setShaderVariable(projectionMatrix,"projectionMatrix");

	for (const Mesh* mesh: this->model->getMeshes()) {
		mesh->getVAO()->bind();

		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, this->texture);
		glDrawArrays(GL_TRIANGLES, 0, mesh->getVertices().size());

		mesh->getVAO()->unbind();
	}

	glDepthMask(GL_TRUE);
}