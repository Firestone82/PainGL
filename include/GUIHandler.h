#pragma once

#include "scene/WindowHandler.h"

#include "3rdparty/imgui/imgui.h"
#include "3rdparty/imgui/backend/imgui_impl_glfw.h"
#include "3rdparty/imgui/backend/imgui_impl_opengl3.h"

class GUIHandler {
	private:
		bool showGui = true;

    public:
		bool showDemo = false;

        explicit GUIHandler(WindowHandler* window);
        ~GUIHandler();

        void handle();
        void render();
        void clear();

		void setShow(bool show);
		bool isShown() const;

		void setDemoShow(bool show);
		bool isDemoShown() const;
};