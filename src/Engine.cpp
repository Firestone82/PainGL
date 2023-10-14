#include "GL/glew.h"
#include <GLFW/glfw3.h>

#include "Engine.h"
#include "Logger.h"

#include "../assets/model/header/plain.h"
#include "../assets/model/header/pyramid.h"
#include "../assets/model/header/sphere.h"
#include "../assets/model/header/triangle.h"

Engine* Engine::instance_ = nullptr;

Engine::Engine() {
    Engine::instance_ = this;
}

Engine::~Engine() {
    delete this->scene;
    this->scene = nullptr;

    delete this->guiHandler;
    this->guiHandler = nullptr;

    delete this->eventHandler;
    this->eventHandler = nullptr;

    delete this->modelHandler;
    this->modelHandler = nullptr;

    delete this->shaderHandler;
    this->shaderHandler = nullptr;

    delete this->guiHandler;
    this->guiHandler = nullptr;

    Engine::instance_ = nullptr;
    glfwTerminate();
}

void Engine::init() {
    if (!glfwInit()) {
        Logger::error("Could not start GLFW3.");
        exit(EXIT_FAILURE);
    }
}

void Engine::run() {
	bool consoleOpen = false;

    while (this->running) {
        glfwPollEvents();

        this->running = !this->scene->getWindowHandler()->shouldClose();
        calculateDeltaTime();

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        this->guiHandler->handle();

        this->scene->tick(this->deltaTime);
        this->scene->draw();

		if (this->guiHandler->isShown()) {
            this->guiHandler->render();
		}

		if (this->guiHandler->isDemoShown()) {
			ImGui::ShowDemoWindow(&this->guiHandler->showDemo);
		}

	    if (this->consoleHandler->isShown()) {
		    this->consoleHandler->render();
	    }

        this->guiHandler->clear();
	    this->scene->getWindowHandler()->swapBuffers();
    }
}

void Engine::stop() {
    this->running = false;
}

bool Engine::isRunning() const {
    return this->running;
}

void Engine::calculateDeltaTime() {
    double temp = lastTime;
    lastTime = glfwGetTime();
    deltaTime = lastTime - temp;
}

double Engine::getDeltaTime() const {
    return this->deltaTime;
}

void Engine::createScene(int width, int height, const char* title) {
    this->scene = new Scene(width, height, title);
    this->scene->getCameraHandler()->setAspectRatio(static_cast<float>(width), static_cast<float>(height));
	this->scene->getCameraHandler()->calculateProjectionMatrix();

    // Start GLEW extension handler
    glewExperimental = GL_TRUE;
    glewInit();

    // Initialize OpenGL graphics settings
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);     // Set background color to black and opaque
    glClearDepth(1.0f);                                        // Set background depth to farthest
    glEnable(GL_DEPTH_TEST);                                     // Enable depth testing for z-culling
    glDepthFunc(GL_LEQUAL);                                     // Set the type of depth-test
    glShadeModel(GL_SMOOTH);                                   // Enable smooth shading
    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);  // Nice perspective corrections

	glfwSwapInterval(1);
}

Scene* Engine::getScene() {
    return this->scene;
}

void Engine::createEventHandler() {
	this->eventHandler = new EventHandler();

    // WindowHandler resize listener
    this->eventHandler->addListener(new Listener<WindowResizeEvent>([=](WindowResizeEvent* event) {
        this->scene->getCameraHandler()->setAspectRatio(event->getNewSize()[0], event->getNewSize()[1]);
	    this->scene->getCameraHandler()->calculateProjectionMatrix();
	    this->scene->getWindowHandler()->setWidth(static_cast<int>(event->getNewSize()[0]));
	    this->scene->getWindowHandler()->setHeight(static_cast<int>(event->getNewSize()[1]));
    }));

    // Exit engine on window close
    this->eventHandler->addListener(new Listener<WindowCloseEvent>([=](WindowCloseEvent* event) {
        Engine::getInstance()->stop();
    }));
}

EventHandler* Engine::getEventHandler() {
    return this->eventHandler;
}

void Engine::createGUI(WindowHandler* window) {
    this->guiHandler = new GUIHandler(window);
}

GUIHandler* Engine::getGUIHandler() {
    return this->guiHandler;
}

void Engine::createShaders(const std::string& folderPath) {
    this->shaderHandler = new ShaderHandler();
    this->shaderHandler->loadShaderFolder(folderPath, ".frag");
    this->shaderHandler->loadShaderFolder(folderPath, ".vert");
}

ShaderHandler* Engine::getShaderHandler() {
    return this->shaderHandler;
}

void Engine::createModels(const std::string& folderPath) {
    this->modelHandler = new ModelHandler();
    this->modelHandler->loadModelFolder(folderPath,".obj");

    this->modelHandler->loadModelVariable("plain", plain);
    this->modelHandler->loadModelVariable("pyramid", pyramid);
    this->modelHandler->loadModelVariable("sphere", sphere);
    this->modelHandler->loadModelVariable("triangle", triangle);
}

ModelHandler* Engine::getModelHandler() {
    return this->modelHandler;
}

void Engine::createConsole() {
	this->consoleHandler = new ConsoleHandler("Console");
}

ConsoleHandler* Engine::getConsoleHandler() {
	return this->consoleHandler;
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

    std::cout << std::endl;
    Logger::warning("OpenGL Version: %s", glGetString(GL_VERSION));
    Logger::warning("Using GLEW: %s", glewGetString(GLEW_VERSION));
    Logger::warning("Vendor: %s", glGetString(GL_VENDOR));
    Logger::warning("Renderer: %s", glGetString(GL_RENDERER));
    Logger::warning("GLSL: %s", glGetString(GL_SHADING_LANGUAGE_VERSION));
    Logger::warning("Using GLFW: %d.%d.%d", major, minor, revision);
    std::cout << std::endl;
}

Engine* Engine::getInstance() {
    return Engine::instance_;
}