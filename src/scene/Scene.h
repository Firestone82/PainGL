#pragma once

#include "window/window.h"
#include "entity/RenderableEntity.h"
#include <vector>
#include <glm/glm.hpp>

class Scene {
    private:
        WindowHandler* windowHandler;
		CameraHandler* cameraHandler;

        std::vector<RenderableEntity*> entities;

        float fieldOfView = 45.0f;
        float aspectRatio = 4.0f / 3.0f;
        glm::vec2 nearFarPlane = glm::vec2(0.01f, 100.0f);

    public:
        Scene(int width, int height, const char* title);
        ~Scene();

        void renderEntity(RenderableEntity* entity);

        void draw();
        void tick(double deltaTime);

        WindowHandler* getWindowHandler();
		CameraHandler* getCameraHandler();

        void setNearFarPlane(glm::vec2 nearFarPlane);
        glm::vec2 getNearFarPlane() const;

        Window* getWindow();
        const std::vector<RenderableEntity*>& getEntities();
};
