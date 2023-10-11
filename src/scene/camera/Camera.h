#pragma once

#include "glm/glm.hpp"

class Camera {
    private:
        float fov = 45.0f;
        float aspectRatio = 4.0f / 3.0f;
        float nearPane = 0.01f;
        float farPane = 100.0f;

        glm::vec3 target = glm::vec3(0.0f, 0.0f, 0.0f);

    public:
        Camera();
        ~Camera();

        void setFov(float fov);
        float getFov() const;

        void setAspectRatio(float aspectRatio);
        float getAspectRatio() const;

        void setNearPane(float nearPane);
        float getNearPane() const;

        void setFarPane(float farPane);
        float getFarPane() const;
};