#pragma once

#include "scene/sky/Sky.h"

class SkyBox : public Sky {
	private:
		SkyBoxImages* images = nullptr;

	public:
		SkyBox(const std::string &name, SkyBoxImages* images);
		~SkyBox();

		void init() override;
		void draw() override;
};