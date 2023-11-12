#pragma once

#include "scene/structure/Transformable.h"
#include "scene/entity/material/Material.h"
#include "shader/ShaderProgram.h"
#include "model/Model.h"
#include "utils/Logger.h"

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
				std::vector<Texture*> textures;
				for (int i = 0; i < mesh->getTextures().size(); i++) textures.push_back(mesh->getTextures()[i]);
				for (int i = 0; i < this->material->getTextures().size(); i++) textures.push_back(this->material->getTextures()[i]);

				this->shaderProgram->setShaderVariable(!textures.empty(), "material.useTexture");

				int diff = 1;
				int spec = 1;
				for (int i = 0; i < textures.size(); i++) {
					std::string varName = "material.texture";

					switch (textures[i]->getTextureType()) {
						case TextureType::DIFFUSE:
							varName += "Diffuse" + std::to_string(diff++);
							break;

						case TextureType::SPECULAR:
							varName += "Specular" + std::to_string(spec++);
							break;

						case UNSPECIFIED:
							break;
					}

					this->shaderProgram->setShaderVariable(i, varName);
					textures[i]->bind(i);
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