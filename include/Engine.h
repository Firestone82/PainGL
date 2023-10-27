#pragma once

#include "event/EventHandler.h"
#include "window/WindowHandler.h"
#include "scene/SceneHandler.h"
#include "shader/ShaderHandler.h"
#include "model/ModelHandler.h"
#include "console/ConsoleHandler.h"
#include "gui/GUIHandler.h"
#include "texture/TextureHandler.h"

class Engine {
	private:
		static Engine* instance_;
		bool running = true;

		// FPS
		int vsync = 1;
		int maxFPS = 60;

		// Time
		double lastTime = 0;
		double deltaTime = 0;

		// Handlers
		WindowHandler* windowHandler;
		SceneHandler* sceneHandler;
		EventHandler* eventHandler;
		ShaderHandler* shaderHandler;
		ModelHandler* modelHandler;
		ConsoleHandler* consoleHandler;
		GUIHandler* guiHandler;
		TextureHandler* textureHandler;

	public:
		static Engine* getInstance();
		~Engine();

		void init(int width, int height, const std::string &title);
		void run();
		void stop();
		bool isRunning() const;

		void setVsync(int vsync);
		int getVsync() const;

		void setMaxFPS(int maxFPS);
		int getMaxFPS() const;
		float getCurrentFPS() const;

		void calculateDeltaTime();
		double getDeltaTime() const;

		WindowHandler* getWindowHandler();
		SceneHandler* getSceneHandler();
		EventHandler* getEventHandler();
		ShaderHandler* getShaderHandler();
		ModelHandler* getModelHandler();
		ConsoleHandler* getConsoleHandler();
		GUIHandler* getGUIHandler();
		TextureHandler* getTextureHandler();

		void setVersion(int major, int minor, bool forwardCompat, int profile);
		void info();

};
