#include "GL/glew.h"
#include <GLFW/glfw3.h>

#include "Engine.h"
#include "Logger.h"

#include "../assets/model/header/plain.h"
#include "../assets/model/header/pyramid.h"
#include "../assets/model/header/sphere.h"
#include "../assets/model/header/triangle.h"
#include "../assets/model/header/gift.h"

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
    this->scene->getCameraHandler()->setAspectRatio(width, height);
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

	// Set default swap interval to 60 FPS
	glfwSwapInterval(1);
}

Scene* Engine::getScene() {
    return this->scene;
}

void Engine::createEventHandler() {
	this->eventHandler = new EventHandler();

    // WindowHandler resize listener
    this->eventHandler->addListener(new Listener<WindowResizeEvent>([=](WindowResizeEvent* event) {
		int width = int(event->getNewSize()[0]);
		int height = int(event->getNewSize()[1]);

        this->scene->getCameraHandler()->setAspectRatio(width, height);
	    this->scene->getCameraHandler()->calculateProjectionMatrix();
	    this->scene->getWindowHandler()->setWidth(width);
	    this->scene->getWindowHandler()->setHeight(height);

	    glViewport(0, 0, width, height);
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
    this->modelHandler->loadModelVariable("gift", gift);
}

ModelHandler* Engine::getModelHandler() {
    return this->modelHandler;
}

void Engine::createConsole() {
	this->consoleHandler = new ConsoleHandler("Developer Console");

	consoleHandler->addCommand(ConsoleCommand::createCommand("help")
						->setDescription("Displays all available commands")
						->setUsage("help")
						->setCallback([=](const std::vector<std::string>& args) {
						    consoleHandler->addLog(false,"\n Commands:");

						    for (const auto& command : consoleHandler->getCommands()) {
						        consoleHandler->addLog(false,"  » %s", command->getUsage().c_str());
						        consoleHandler->addLog(false,"     # %s", command->getDescription().c_str());
						    }
						})
						->build());

	consoleHandler->addCommand(ConsoleCommand::createCommand("clear")
						->setDescription("Clears the console")
						->setUsage("clear")
						->setCallback([=](const std::vector<std::string>& args) {
							consoleHandler->clearLog();
						})
						->build());

	consoleHandler->addCommand(ConsoleCommand::createCommand("position")
						->setDescription("Sets the position of the camera")
						->setUsage("position <x> <y> <z>")
						->setMinArgs(3)
						->setMaxArgs(3)
						->setCallback([=](const std::vector<std::string>& args) {
							float x;
							float y;
							float z;

                            try {
                                x = std::stof(args[1]);
                                y = std::stof(args[2]);
                                z = std::stof(args[3]);
                            } catch (std::exception& e) {
                                consoleHandler->addLog(false, "[error] %s", e.what());
                                return;
                            }

                            scene->getCameraHandler()->getCamera()->setPosition(glm::vec3(x, y, z));
                            scene->getCameraHandler()->getCamera()->calculateViewMatrix();

                            consoleHandler->addLog(false,"\n Camera position set to (%0.2f, %0.2f, %0.2f)", x, y, z);
						})
						->build());

	consoleHandler->addCommand(ConsoleCommand::createCommand("target")
						->setDescription("Sets the target of the camera")
						->setUsage("target <x> <y> <z>")
						->setMinArgs(3)
						->setMaxArgs(3)
						->setCallback([=](const std::vector<std::string>& args) {
						    float x;
						    float y;
						    float z;

						    try {
						        x = std::stof(args[1]);
						        y = std::stof(args[2]);
						        z = std::stof(args[3]);
						    } catch (std::exception& e) {
						        consoleHandler->addLog(false, "[error] %s", e.what());
						        return;
						    }

						    scene->getCameraHandler()->getCamera()->setTarget(glm::vec3(x, y, z));
						    scene->getCameraHandler()->getCamera()->calculateViewMatrix();

						    consoleHandler->addLog(false, "\n Camera target set to (%0.2f, %0.2f, %0.2f)", x, y, z);
						})
						->build());

	consoleHandler->addCommand(ConsoleCommand::createCommand("sensitivity")
						->setDescription("Sets the sensitivity of the camera")
						->setUsage("sensitivity <sensitivity>")
						->setMinArgs(0)
						->setMaxArgs(1)
						->setCallback([=](const std::vector<std::string>& args) {
						    float sensitivity = scene->getCameraHandler()->getSensitivity();

						    if (args.size() == 1) {
						        consoleHandler->addLog(false, "\n Camera sensitivity is %0.2f", sensitivity);
						        return;
						    }

						    try {
						        sensitivity = std::stof(args[1]);
						        scene->getCameraHandler()->setSensitivity(sensitivity);
						    } catch (std::exception& e) {
						        consoleHandler->addLog(false, "[error] %s", e.what());
						        return;
						    }

						    consoleHandler->addLog(false, "\n Camera sensitivity set to %0.2f", sensitivity);
						})
						->build());

	consoleHandler->addCommand(ConsoleCommand::createCommand("speed")
						->setDescription("Sets the speed of the camera")
						->setUsage("speed <speed>")
						->setMinArgs(0)
						->setMaxArgs(1)
						->setCallback([=](const std::vector<std::string>& args) {
						    float speed = scene->getCameraHandler()->getSpeed();

						    if (args.size() == 1) {
						        consoleHandler->addLog(false, "\n Camera speed is %0.2f", speed);
						        return;
						    }

						    try {
						        speed = std::stof(args[1]);
						        scene->getCameraHandler()->setSpeed(speed);
						    } catch (std::exception& e) {
						        consoleHandler->addLog(false, "[error] %s", e.what());
						        return;
						    }

						    consoleHandler->addLog(false, "\n Camera speed set to %0.2f", speed);
						})
						->build());

	consoleHandler->addCommand(ConsoleCommand::createCommand("fov")
						->setDescription("Sets the field of view of the camera")
						->setUsage("fov <fov>")
						->setMinArgs(0)
						->setMaxArgs(1)
						->setCallback([=](const std::vector<std::string>& args) {
						    float fov = scene->getCameraHandler()->getFov();

						    if (args.size() == 1) {
						        consoleHandler->addLog(false, "\n Camera fov is %0.2f", fov);
						        return;
						    }

						    try {
						        fov = std::stof(args[1]);
						        scene->getCameraHandler()->setFov(fov);
						        scene->getCameraHandler()->calculateProjectionMatrix();
						    } catch (std::exception& e) {
						        consoleHandler->addLog(false, "[error] %s", e.what());
						        return;
						    }

						    consoleHandler->addLog(false, "\n Camera fov set to %0.2f", fov);
						})
						->build());

	// TODO: Max FPS command

	// TODO: Static delta time command

	consoleHandler->addCommand(ConsoleCommand::createCommand("demo")
						->setDescription("Toggle demo window")
						->setUsage("demo")
						->setCallback([=](const std::vector<std::string>& args) {
						    bool state = guiHandler->isDemoShown();

						    guiHandler->setDemoShow(!state);
						    scene->getCameraHandler()->setMoving(false);

						    if (!state) {
						        consoleHandler->setShown(false);
								scene->getCameraHandler()->setMoving(false);
						    }

						    consoleHandler->addLog(false, "\n Demo window %s", state ? "hidden" : "shown");
						})
						->build());

	consoleHandler->addCommand(ConsoleCommand::createCommand("vsync")
						->setDescription("Toggle vsync between 20fps, 30fps, 60fps and unlimited")
						->setUsage("vsync <0,1,2,3>")
						->setMinArgs(1)
						->setMaxArgs(1)
						->setCallback([=](const std::vector<std::string>& args) {
						    float sync;

						    try {
						        sync = std::stof(args[1]);
						    } catch (std::exception& e) {
						        consoleHandler->addLog(false, "[error] %s", e.what());
						        return;
						    }

						    if (sync < 0 || sync > 3) {
						        consoleHandler->addLog(false, "[error] Vsync must be 0, 1, 2 or 3");
						        return;
						    }

						    glfwSwapInterval(int(sync));
						    int fps = int(60 / sync);

						    consoleHandler->addLog(false, "\n Vsync changed to %d (%d fps)", static_cast<int>(sync), (sync == 0 ? 2000 : fps));
						})
						->build());

	consoleHandler->addCommand(ConsoleCommand::createCommand("gui")
						->setDescription("Toggle GUI from rendering")
						->setUsage("gui")
						->setCallback([=](const std::vector<std::string>& args) {
							bool state = guiHandler->isShown();
							guiHandler->setShow(!state);
							consoleHandler->addLog(false, "\n GUI %s", state ? "disabled" : "enabled");
						})
						->build());

	consoleHandler->addCommand(ConsoleCommand::createCommand("quit")
	                    ->setDescription("Quit application")
	                    ->setUsage("quit")
	                    ->setCallback([=](const std::vector<std::string>& args) {
					 	   stop();
	                    })
	                    ->build());
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