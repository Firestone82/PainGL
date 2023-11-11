#pragma once

#include "scene/structure/Transformable.h"
#include "scene/entity/material/Material.h"
#include "shader/ShaderProgram.h"
#include "model/Model.h"

#include <functional>

class Renderable : public Transformable {
	protected:
		Model* model;
		ShaderProgram* shaderProgram;
		Material* material;

		Renderable() = default;
		~Renderable() {
			this->model = nullptr;
			this->shaderProgram = nullptr;
			delete this->material;
		}

	public:
		virtual void draw() {
			this->shaderProgram->use();

			// Model
			// TODO: Make entity static and dynamic
			this->shaderProgram->setShaderVariable(this->matrix, "modelMatrix");
			this->shaderProgram->setShaderVariable(glm::transpose(glm::inverse(glm::mat3(this->matrix))), "normalMatrix");

			// Material
			this->shaderProgram->setShaderVariable(this->material->getDiffuseColor(), "material.diffuse");
			this->shaderProgram->setShaderVariable(this->material->getSpecularColor(), "material.specular");
			this->shaderProgram->setShaderVariable(this->material->getShininess(), "material.shininess");
			this->shaderProgram->setShaderVariable(this->material->getTextureScale(), "scale");

			for (const Mesh* mesh: this->model->getMeshes()) {
				this->shaderProgram->setShaderVariable(!mesh->getTextures().empty(), "material.useTexture");
				this->shaderProgram->setShaderVariable(false, "material.useNormalMap");

				int diff = 1;
				int spec = 1;
				int norm = 1;
				for (int i = 0; i < mesh->getTextures().size(); i++) {
					std::string varName = "material.texture";

					switch (mesh->getTextures()[i]->getTextureType()) {
						case TextureType::DIFFUSE:
							varName += "Diffuse" + std::to_string(diff++);
							break;

						case TextureType::SPECULAR:
							varName += "Specular" + std::to_string(spec++);
							break;

						case TextureType::NORMAL:
							varName += "Normal" + std::to_string(norm++);
							break;

						case UNSPECIFIED:
							break;
					}

					if (norm == 2) {
						this->shaderProgram->setShaderVariable(true, "material.useNormalMap");
					}

					this->shaderProgram->setShaderVariable(i, varName);
					mesh->getTextures()[i]->bind(i);
				}

				mesh->getVAO()->bind();

				if (mesh->getIndices().empty()) {
					glDrawArrays(GL_TRIANGLES, 0, mesh->getVertices().size());
				} else {
					mesh->getEBO()->bind();
					glDrawElements(GL_TRIANGLES, mesh->getIndices().size(), GL_UNSIGNED_INT, nullptr);
					mesh->getEBO()->unbind();
				}

				mesh->getVAO()->unbind();

				for (int i = 0; i < mesh->getTextures().size(); i++) {
					mesh->getTextures()[i]->unbind();
				}
			}

			this->shaderProgram->unUse();
		}

		Model* getModel() const {
			return this->model;
		}

		ShaderProgram* getShaderProgram() const {
			return this->shaderProgram;
		}

		Material* getMaterial() {
			return this->material;
		}
};