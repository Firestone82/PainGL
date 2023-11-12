#include "utils/Logger.h"
#include "model/Model.h"
#include "Engine.h"
#include "scene/sky/skybox/SkyBox.h"

SkyBox::SkyBox(const std::string &name, SkyBoxImages* images) : Sky(name) {
	this->id = 0;
	this->model = Engine::getInstance()->getModelHandler()->getModel("cube");
	this->shaderProgram = Engine::getInstance()->getShaderHandler()->createProgram("skybox.vert", "skybox.frag");
	this->images = images;

	this->init();
}

SkyBox::~SkyBox() {
	this->model = nullptr;
	this->shaderProgram = nullptr;
	delete this->images;

	glDeleteTextures(1, &this->texture);
	this->texture = 0;
}

void SkyBox::init() {
	this->texture = 0;
	glGenTextures(1, &this->texture);
	glBindTexture(GL_TEXTURE_CUBE_MAP, this->texture);

	std::vector<Image*> loadedImages;
	loadedImages.emplace_back(new Image(images->right));
	loadedImages.emplace_back(new Image(images->left));
	loadedImages.emplace_back(new Image(images->top));
	loadedImages.emplace_back(new Image(images->bottom));
	loadedImages.emplace_back(new Image(images->front));
	loadedImages.emplace_back(new Image(images->back));

	for (GLuint i = 0; i < loadedImages.size(); i++) {
		Image* image = loadedImages[i];
		glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGB, image->getWidth(), image->getHeight(), 0, GL_RGB, GL_UNSIGNED_BYTE, image->getData());
	}

	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

	for (Image* image: loadedImages) {
		delete image;
	}
}

void SkyBox::draw() {
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
		glBindTexture(GL_TEXTURE_CUBE_MAP, this->texture);
		glDrawArrays(GL_TRIANGLES, 0, mesh->getVertices().size());

		mesh->getVAO()->unbind();
	}

	glDepthMask(GL_TRUE);
}