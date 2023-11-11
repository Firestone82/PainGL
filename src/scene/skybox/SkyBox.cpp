#include "scene/skybox/SkyBox.h"
#include "utils/Logger.h"
#include "model/Model.h"
#include "Engine.h"

SkyBox::SkyBox(const std::string &name, std::vector<Path> images) : Object(name) {
	this->id = 0;

	this->model = Engine::getInstance()->getModelHandler()->getModel("cube");
	this->shaderProgram = Engine::getInstance()->getShaderHandler()->createProgram("skybox.vert", "skybox.frag");

	std::vector<Image*> loadedImages;
	for (Path imagePath: images) {
		loadedImages.push_back(new Image(imagePath));
	}

	this->texture = 0;
	glGenTextures(1, &this->texture);
	glBindTexture(GL_TEXTURE_CUBE_MAP, this->texture);

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

SkyBox::~SkyBox() {
	this->model = nullptr;
	this->shaderProgram = nullptr;
}

void SkyBox::draw() {
	glDepthFunc(GL_LEQUAL);

	Scene* scene = Engine::getInstance()->getSceneHandler()->getActiveScene();
	glm::mat4 view = glm::mat4(glm::mat3(scene->getCameraHandler()->getCamera()->getViewMatrix()));
	glm::mat4 projection = scene->getCameraHandler()->getProjectionMatrix();

	this->shaderProgram->use();
	this->shaderProgram->setShaderVariable(0,"skybox");
	this->shaderProgram->setShaderVariable(view,"view");
	this->shaderProgram->setShaderVariable(projection,"projection");

	for (const Mesh* mesh: this->model->getMeshes()) {
		mesh->getVAO()->bind();

		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_CUBE_MAP, this->texture);
		glDrawArrays(GL_TRIANGLES, 0, mesh->getVertices().size());

		mesh->getVAO()->unbind();
	}

	glDepthFunc(GL_LESS);
}