#pragma once

#include <string>
#include <functional>

class GUI {
	private:
		std::string name;
		std::function<void(GUI*, float&)> drawFunction;

	public:
		GUI(const std::string& name, const std::function<void(GUI*, float&)> &drawFunction);

		void render(float &top);

		void setName(const std::string &name);
		std::string getName() const;
};