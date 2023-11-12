#pragma once

#include "scene/sky/Sky.h"
#include "scene/sky/skydome/SkyDome.h"

class SkySphere : public SkyDome {
	public:
		SkySphere(const std::string &name, Path* image);
};