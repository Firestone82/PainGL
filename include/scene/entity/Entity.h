#pragma once

#include "scene/entity/material/Material.h"
#include "scene/structure/Transformable.h"
#include "scene/structure/Randerable.h"
#include "scene/structure/Simulable.h"
#include "scene/structure/Object.h"
#include "shader/ShaderProgram.h"
#include "model/Model.h"

class Entity : public Object, public Renderable, public Simulable<Entity> {
	protected:
		explicit Entity(const std::string &name) : Object(name) {};

	public:
		~Entity() override;

		class Builder {
			private:
				Entity* entity;

			public:
				Builder(const std::string &name);

				Builder& setModel(const std::string &model);
				Builder& setShaderProgram(const std::string &vertex, const std::string &fragment);
				Builder& setShaderProgram(ShaderProgram* shaderProgram);
				Builder& setMaterial(Material* material);
				Builder& setTransformation(Transform::Composite* composite);
				Builder& setSimulateFunction(const std::function<void(Entity*, float)> &simulateFunction);
				Builder& addTexture(const std::string &texture, TextureType type);

				Entity* build();
		};

		static Builder createEntity(const std::string &name);
};