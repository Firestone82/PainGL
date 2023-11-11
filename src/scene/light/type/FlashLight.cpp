#include "scene/light/type/FlashLight.h"
#include "event/type/CameraEvents.h"
#include "event/type/SceneEvents.h"
#include "Engine.h"
#include "utils/Logger.h"

FlashLight::FlashLight(const std::string &name) : AbstractLight(name, LightType::SPOT_LIGHT) {
	static std::function updateLight = [=]() {
        Scene* activeScene = Engine::getInstance()->getSceneHandler()->getActiveScene();

        // Ignore lights out of active scene
        std::vector<AbstractLight*> lights = activeScene->getLightHandler()->getLights();
        if (std::find(lights.begin(), lights.end(), this) == lights.end()) return;

		Camera* camera = Engine::getInstance()->getSceneHandler()->getActiveScene()->getCameraHandler()->getCamera();
		position = camera->getPosition();
		direction = camera->getTarget();

		update();
	};

	// Listener for scene switch
	Engine::getInstance()->getEventHandler()->addListener(new Listener<SceneSwitchEvent>([=](SceneSwitchEvent* event) {
		updateLight();
	}));

	// Listener for camera movement
	Engine::getInstance()->getEventHandler()->addListener(new Listener<CameraMoveEvent>([=](CameraMoveEvent* event) {
		updateLight();
	}));

	// Listener for camera rotation
	Engine::getInstance()->getEventHandler()->addListener(new Listener<CameraRotateEvent>([=](CameraRotateEvent* event) {
		updateLight();
	}));
};

glm::vec3 FlashLight::getDirection() {
	return this->direction;
}

void FlashLight::setAttenuation(const Attenuation &attenuation) {
	this->attenuation = attenuation;
	update();
}

Attenuation FlashLight::getAttenuation() {
	return this->attenuation;
}

void FlashLight::setCutOff(float cutOff) {
	this->cutOff[0] = cutOff;
	update();
}

float FlashLight::getCutOff() {
	return this->cutOff[0];
}

void FlashLight::setOuterCutOff(float outerCutOff) {
	this->cutOff[1] = outerCutOff;
	update();
}

float FlashLight::getOuterCutOff() {
	return this->cutOff[1];
}

std::map<std::string, std::variant<glm::vec3, float>> FlashLight::getShaderVariables() const {
	std::map<std::string, std::variant<glm::vec3, float>> variables = AbstractLight::getShaderVariables();
	variables["position"] = this->position;
	variables["direction"] = this->direction;
	variables["constant"] = this->attenuation.constant;
	variables["linear"] = this->attenuation.linear;
	variables["quadratic"] = this->attenuation.quadratic;
	variables["cutOff"] = this->cutOff[0];
	variables["outerCutOff"] = this->cutOff[1];

	return variables;
}

// -- Builder --

FlashLight::Builder::Builder(const std::string &name) {
	this->object = new FlashLight(name);
}

FlashLight::Builder& FlashLight::Builder::setColor(glm::vec3 color) {
	this->object->setColor(color);
	return *this;
}

FlashLight::Builder& FlashLight::Builder::setAmbient(glm::vec3 ambient) {
	this->object->ambient = ambient;
	return *this;
}

FlashLight::Builder& FlashLight::Builder::setDiffuse(glm::vec3 diffuse) {
	this->object->diffuse = diffuse;
	return *this;
}

FlashLight::Builder& FlashLight::Builder::setSpecular(glm::vec3 specular) {
	this->object->specular = specular;
	return *this;
}

FlashLight::Builder& FlashLight::Builder::setAttenuation(const Attenuation &attenuation) {
	this->object->attenuation = attenuation;
	return *this;
}

FlashLight::Builder& FlashLight::Builder::setCutOff(float cutOff) {
	this->object->cutOff[0] = cutOff;
	return *this;
}

FlashLight::Builder& FlashLight::Builder::setOuterCutOff(float outerCutOff) {
	this->object->cutOff[1] = outerCutOff;
	return *this;
}

FlashLight* FlashLight::Builder::build() {
	return this->object;
}

FlashLight::Builder FlashLight::createLight(const std::string &name) {
	return Builder(name);
}