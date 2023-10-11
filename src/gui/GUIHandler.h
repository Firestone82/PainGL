#pragma once

#include "../scene/window/Window.h"

#include "imgui/imgui.h"
#include "imgui/backend/imgui_impl_glfw.h"
#include "imgui/backend/imgui_impl_opengl3.h"

class GUIHandler {
    public:
        explicit GUIHandler(Window* window);
        ~GUIHandler();

        void handle();
        void render();
        void clear();
};