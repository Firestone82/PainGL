#pragma once

#include "scene/sky/Sky.h"

class SkyDome : public Sky {
	private:
		Path* image = nullptr;

	public:
		SkyDome(const std::string &name, Path* image);
		~SkyDome();

		void init() override;
		void draw() override;
};