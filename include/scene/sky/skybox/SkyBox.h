#pragma once

#include "scene/sky/Sky.h"

class SkyBox : public Sky {
	public:
		SkyBox(const std::string &name, SkyBoxImages images);
		~SkyBox();

		void draw() override;
};