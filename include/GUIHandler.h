#pragma once

#include "../src/scene/window/WindowHandler.h"

#include "imgui/imgui.h"
#include "imgui/backend/imgui_impl_glfw.h"
#include "imgui/backend/imgui_impl_opengl3.h"

class GUIHandler {
    public:
        explicit GUIHandler(WindowHandler* window);
        ~GUIHandler();

        void handle();
        void render();
        void clear();
};