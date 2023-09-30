#pragma once

#include "../scene/Scene.h"
#include "../listener/EventHandler.h"
#include "../shader/ShaderHandler.h"
#include "../model/ModelHandler.h"

class Engine {
    private:
        bool running = true;
        double lastTick = 0;

        Scene* scene = nullptr;
        EventHandler* eventHandler = nullptr;
        ShaderHandler* shaderHandler = nullptr;
        ModelHandler* modelHandler = nullptr;

    public:
        Engine() = default;
        ~Engine();

        void init();
        void createScene(int width, int height, const char* title);
        void createShaders();
        void createModels();

        void setVersion(int major, int minor, bool forwardCompat, int profile);
        void info();

        void run();
        void stop();
        bool isRunning() const;

        Scene* getScene();
        EventHandler* getEventHandler();
        ShaderHandler* getShaderHandler();
        ModelHandler* getModelHandler();
};
