#include "utils/Logger.h"
#include "model/Model.h"
#include "Engine.h"
#include "scene/sky/skydome/SkyDome.h"
#include "scene/sky/skysphere/SkySphere.h"

SkySphere::SkySphere(const std::string &name, Path* image) : SkyDome(name, image) {
	this->model = Engine::getInstance()->getModelHandler()->getModel("sphere");
}