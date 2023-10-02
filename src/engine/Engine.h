#pragma once

#include "../scene/Scene.h"
#include "../listener/EventHandler.h"
#include "../shader/ShaderHandler.h"
#include "../model/ModelHandler.h"

class Engine {
    private:
        bool running = true;
        double lastTick = 0;

        Scene* scene;
        EventHandler* eventHandler;
        ShaderHandler* shaderHandler;
        ModelHandler* modelHandler;

    public:
        Engine();
        ~Engine();

        void init();
        void run();
        void stop();
        bool isRunning() const;
        double getDeltaTime() const;

        void createScene(int width, int height, const char *title);
        Scene* getScene();

        void createEventHandler(Window* window);
        EventHandler* getEventHandler();

        void createGUI(Window* window);
        GUI* getGUI();

        void createShaders(const std::string& folderPath);
        ShaderHandler* getShaderHandler();

        void createModels(const std::string& folderPath);
        ModelHandler* getModelHandler();

        void setVersion(int major, int minor, bool forwardCompat, int profile);
        void info();
};
