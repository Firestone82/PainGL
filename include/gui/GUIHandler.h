#pragma once

#include "gui/GUI.h"

#include <vector>

class GUIHandler {
	private:
		bool showGui = true;
		bool showDemo = false;

		std::vector<GUI*> guis;
		void fillGUIs();

	public:
		GUIHandler();
		~GUIHandler();

		void handle();
		void render();
		void clear();

		void addGUI(GUI* gui);
		void removeGUI(GUI* gui);

		void setEnabled(bool enable);
		bool isEnabled() const;

		void setDemoEnabled(bool enable);
		bool isDemoEnabled() const;
};