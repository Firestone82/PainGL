#pragma once

#include "scene/Scene.h"
#include "listener/EventHandler.h"
#include "shader/ShaderHandler.h"
#include "model/ModelHandler.h"
#include "GUIHandler.h"
#include "console/ConsoleHandler.h"

class Engine {
    private:
        static Engine* instance_;

        bool running = true;
        double lastTime = 0;
        double deltaTime = 0;

        Scene* scene;
        GUIHandler* guiHandler;
        EventHandler* eventHandler;
        ShaderHandler* shaderHandler;
        ModelHandler* modelHandler;
		ConsoleHandler* consoleHandler;

    public:
        Engine();
        ~Engine();

        void init();
        void run();
        void stop();
        bool isRunning() const;

        void calculateDeltaTime();
        double getDeltaTime() const;

        void createScene(int width, int height, const char *title);
        Scene* getScene();

        void createEventHandler();
        EventHandler* getEventHandler();

        void createGUI(WindowHandler* window);
        GUIHandler* getGUIHandler();

        void createShaders(const std::string& folderPath);
        ShaderHandler* getShaderHandler();

        void createModels(const std::string& folderPath);
        ModelHandler* getModelHandler();

		void createConsole();
		ConsoleHandler* getConsoleHandler();

        void setVersion(int major, int minor, bool forwardCompat, int profile);
        void info();

        static Engine* getInstance();
};
