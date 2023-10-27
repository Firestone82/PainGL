#pragma once

#include "scene/entity/material/Material.h"
#include "scene/structure/Object.h"
#include "model/Model.h"
#include "shader/ShaderProgram.h"

class Entity : public Object<Entity> {
	private:
		Model* model = nullptr;
		ShaderProgram* shaderProgram = nullptr;
		Material* material = nullptr;

		explicit Entity(const std::string &name) : Object(name) {};

	public:
		~Entity() override;

		void draw() override;

		Model* getModel() const;
		ShaderProgram* getShaderProgram() const;
		Material* getMaterial() const;

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
				Builder* setMaterial(Material* material);
				Builder* setTransformation(Transform::Composite* composite);
				Builder* setSimulateFunction(const std::function<void(Entity*, float)> &simulateFunction);

				Entity* build();
		};

		static Builder* createEntity(const std::string &name);
};