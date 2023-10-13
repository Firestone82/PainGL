#pragma once

#include "window/WindowHandler.h"
#include "entity/RenderableEntity.h"
#include "camera/CameraHandler.h"
#include <vector>
#include <glm/glm.hpp>

class Scene {
    private:
        WindowHandler* windowHandler;
		CameraHandler* cameraHandler;

        std::vector<RenderableEntity*> entities;

    public:
        Scene(int width, int height, const char* title);
        ~Scene();

        void renderEntity(RenderableEntity* entity);
		void disposeEntity(RenderableEntity* entity);

        void draw();
        void tick(double deltaTime);

        WindowHandler* getWindowHandler();
		CameraHandler* getCameraHandler();

        const std::vector<RenderableEntity*>& getEntities();
};
