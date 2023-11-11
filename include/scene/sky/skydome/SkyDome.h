#pragma once

#include "scene/sky/Sky.h"

class SkyDome : public Sky {
	public:
		SkyDome(const std::string &name, Path image);
		~SkyDome();

		void draw() override;
};