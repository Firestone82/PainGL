#pragma once

#include "scene/structure/Object.h"
#include "model/Model.h"
#include "shader/ShaderProgram.h"

class Entity : public Object<Entity> {
	private:
		Model* model = nullptr;
		ShaderProgram* shaderProgram = nullptr;

		// TODO: Move to Material class
		glm::vec3 ambientColor = glm::vec3(0.1f, 0.1f, 0.1f);
		glm::vec3 objectColor = glm::vec3(1.0f, 1.0f, 1.0f);
		float specular = 1.0f;
		float shininess = 32.0f;

		explicit Entity(const std::string &name) : Object(name) {};

	public:
		~Entity() override;

		void draw() override;

		Model* getModel() const;
		ShaderProgram* getShaderProgram() const;

		glm::vec3 getAmbientColor() const;
		glm::vec3 getObjectColor() const;
		float getSpecular() const;
		float getShininess() const;

		class Builder {
			private:
				Entity* renderableEntity;

			public:
				explicit Builder(const std::string &name);

				Builder* setModel(Model* model);
				Builder* setModel(const std::string &model);
				Builder* setShaderProgram(ShaderProgram* shaderProgram);
				Builder* setShaderProgram(const std::string &vertex, const std::string &fragment);
				Builder* setStatik(bool statik);
				Builder* setObjectColor(glm::vec3 color);
				Builder* setAmbientColor(glm::vec3 color);
				Builder* setSpecular(float specular);
				Builder* setShininess(float shininess);
				Builder* setTransformation(Transform::Composite* composite);
				Builder* setSimulateFunction(const std::function<void(Entity*, float)> &simulateFunction);

				Entity* build();
		};

		static Builder* createEntity(const std::string &name);
};