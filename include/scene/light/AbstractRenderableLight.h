#pragma once

#include "scene/light/AbstractLight.h"
#include "scene/structure/Object.h"
#include "scene/entity/Entity.h"
#include "shader/ShaderProgram.h"
#include "model/Model.h"

class AbstractRenderableLight : public AbstractLight, public Renderable {
	protected:
		LightType type = LightType::POINT_LIGHT;

	public:
		/* - */ AbstractRenderableLight(const std::string &name, LightType type);
		virtual ~AbstractRenderableLight() = default;

		virtual std::map<std::string, std::variant<glm::vec3, float>> getShaderVariables() const;
};