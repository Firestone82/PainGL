#pragma once

#include <map>

#include "scene/structure/Object.h"
#include "scene/entity/Entity.h"
#include "shader/ShaderProgram.h"
#include "model/Model.h"

enum class LightType {
	POINT_LIGHT,
	DIRECTIONAL_LIGHT,
	SPOT_LIGHT,
	FLASH_LIGHT
};

struct Attenuation {
	float constant = 1.0f;
	float linear = 0.1f;
	float quadratic = 0.01f;
};

class AbstractLight : public Object {
	protected:
		LightType type = LightType::POINT_LIGHT;

		glm::vec3 ambient = glm::vec3(0.1f, 0.1f, 0.1f);
		glm::vec3 diffuse = glm::vec3(0.5f, 0.5f, 0.5f);
		glm::vec3 specular = glm::vec3(1.0f, 1.0f, 1.0f);

		AbstractLight(const std::string &name, LightType type);

	public:
		virtual ~AbstractLight() = default;

		void setColor(glm::vec3 color);
		glm::vec3 getColor() const;

		void setAmbient(glm::vec3 rgb);
		glm::vec3 getAmbient() const;

		void setDiffuse(glm::vec3 rgb);
		glm::vec3 getDiffuse() const;

		void setSpecular(glm::vec3 rgb);
		glm::vec3 getSpecular() const;

		LightType getType() const;
		void update();

		virtual std::map<std::string, std::variant<glm::vec3, float>> getShaderVariables() const;
};