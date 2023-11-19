#include "scene/sky/skysphere/SkySphere.h"
#include "Engine.h"

SkySphere::SkySphere(const std::string &name, Path* image) : SkyDome(name, image) {
	this->model = Engine::getInstance()->getModelHandler()->getModel("sphere");
}