#include "Engine.h"
#include "utils/Logger.h"

#include "GL/glew.h"
#include "event/type/SceneEvents.h"
#include <GLFW/glfw3.h>

Engine* Engine::instance_ = nullptr;
Engine* Engine::getInstance() {
	if (Engine::instance_ == nullptr) {
		Engine::instance_ = new Engine();
	}

	return Engine::instance_;
}

Engine::~Engine() {
	delete this->sceneHandler;
	delete this->consoleHandler;
	delete this->guiHandler;
	delete this->shaderHandler;
	delete this->modelHandler;
	delete this->windowHandler;
	delete this->eventHandler;
	delete this->textureHandler;

	Engine::instance_ = nullptr;
	glfwTerminate();
}

void Engine::init(int width, int height, const std::string &title) {
	if (!glfwInit()) {
		Logger::error(" - GLFW3 initialization failed!");
		this->stop();
		exit(EXIT_FAILURE);
	} else {
		Logger::info(" - GLFW3 initialized successfully!");
	}

	this->eventHandler = new EventHandler();
	this->windowHandler = new WindowHandler(width, height, title.c_str());

	// Initialize OpenGL graphics settings
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);     // Set background color to black and opaque
	glClearDepth(1.0f);                                        // Set background depth to farthest
	glEnable(GL_DEPTH_TEST);                                     // Enable depth testing for z-culling
	glDepthFunc(GL_LEQUAL);                                     // Set the type of depth-test
	glShadeModel(GL_SMOOTH);                                   // Enable smooth shading
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);  // Nice perspective corrections
	Logger::info(" - OpenGL initialized successfully! \n");

	// Set default swap interval to 60 FPS
	glfwSwapInterval(this->vsync);
	this->maxFPS = 60;

	this->sceneHandler = new SceneHandler();
	this->shaderHandler = new ShaderHandler("../assets/shader", true);
	this->modelHandler = new ModelHandler("../assets/model", false);
	this->textureHandler = new TextureHandler("../assets/texture", true);
	this->consoleHandler = new ConsoleHandler("Developer Console");
	this->guiHandler = new GUIHandler();
}

void Engine::run() {
	if (this->sceneHandler->getScenes().empty()) {
		Logger::error("No scenes loaded!");
		this->stop();
		exit(EXIT_FAILURE);
	}

	// Scene changed, recalculate camera
	EventHandler::callEvent(new SceneSwitchEvent(nullptr, this->sceneHandler->getActiveScene()));

	while (this->running) {
		glfwPollEvents();

		this->running = !this->getWindowHandler()->shouldClose();
		calculateDeltaTime();

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		this->guiHandler->handle();

		Scene* scene = this->sceneHandler->getActiveScene();
		if (scene != nullptr) {
			scene->simulate(this->deltaTime);
			scene->render();
		}

		if (this->guiHandler->isEnabled()) {
			this->guiHandler->render();
		}

		if (this->consoleHandler->isEnabled()) {
			this->consoleHandler->render();
		}

		this->guiHandler->clear();
		this->getWindowHandler()->swapBuffers();
	}
}

void Engine::stop() {
	this->running = false;
}

bool Engine::isRunning() const {
	return this->running;
}

void Engine::calculateDeltaTime() {
	double currentTime = glfwGetTime();
	this->deltaTime = currentTime - this->lastTime;
	this->lastTime = currentTime;
}

double Engine::getDeltaTime() const {
	return this->deltaTime;
}

WindowHandler* Engine::getWindowHandler() {
	return this->windowHandler;
}

SceneHandler* Engine::getSceneHandler() {
	return this->sceneHandler;
}

EventHandler* Engine::getEventHandler() {
	return this->eventHandler;
}

ShaderHandler* Engine::getShaderHandler() {
	return this->shaderHandler;
}

ModelHandler* Engine::getModelHandler() {
	return this->modelHandler;
}

ConsoleHandler* Engine::getConsoleHandler() {
	return this->consoleHandler;
}

GUIHandler* Engine::getGUIHandler() {
	return this->guiHandler;
}

TextureHandler* Engine::getTextureHandler() {
	return this->textureHandler;
}

void Engine::setVsync(int vsync) {
	this->vsync = vsync;
	glfwSwapInterval(this->vsync);
}

int Engine::getVsync() const {
	return this->vsync;
}

void Engine::setMaxFPS(int maxFPS) {
	this->maxFPS = maxFPS;
}

int Engine::getMaxFPS() const {
	return this->maxFPS;
}

float Engine::getCurrentFPS() const {
	return 1.0f / float(this->deltaTime);
}

void Engine::setVersion(int major, int minor, bool forwardCompat, int profile) {
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, major);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, minor);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, forwardCompat);
	glfwWindowHint(GLFW_OPENGL_PROFILE, profile);
}

void Engine::info() {
	int major, minor, revision;
	glfwGetVersion(&major, &minor, &revision);

	Logger::warning("");
	Logger::warning("OpenGL Version: %s", glGetString(GL_VERSION));
	Logger::warning("Using GLEW: %s", glewGetString(GLEW_VERSION));
	Logger::warning("Vendor: %s", glGetString(GL_VENDOR));
	Logger::warning("Renderer: %s", glGetString(GL_RENDERER));
	Logger::warning("GLSL: %s", glGetString(GL_SHADING_LANGUAGE_VERSION));
	Logger::warning("Using GLFW: %d.%d.%d", major, minor, revision);
	Logger::warning("");
}