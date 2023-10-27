#include "gui/GUI.h"

GUI::GUI(const std::string &name, const std::function<void(GUI*, float&)> &drawFunction) : name(name), drawFunction(drawFunction) {
	/* Empty */
}

void GUI::render(float &top) {
	this->drawFunction(this,top);
}

std::string GUI::getName() const {
	return this->name;
}

void GUI::setName(const std::string &name) {
	this->name = name;
}