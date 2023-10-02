#pragma once


#include "../scene/Scene.h"
#include "../listener/EventHandler.h"
#include "../gui/GUI.h"
#include "../shader/ShaderHandler.h"
#include "../model/ModelHandler.h"

class Engine {
    private:
        bool running = true;
        double deltaTime = 0;
        double lastTime = 0;

        Scene* scene;
        GUI* gui;
        EventHandler* eventHandler;
        ShaderHandler* shaderHandler;
        ModelHandler* modelHandler;

    public:
        Engine() = default;
        ~Engine();

        void init();
        void run();
        void stop();
        bool isRunning() const;

        void calculateDeltaTime();
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
