#include "GL/glew.h"
#include <GLFW/glfw3.h>

#include "Engine.h"

#include "../../assets/model/sphere.h"
#include "../../assets/model/suzi_flat.h"
#include "../../assets/model/suzi_smooth.h"
#include "../../assets/model/triangle.h"
#include "../../assets/model/pyramid.h"

Engine::~Engine() {
    delete this->scene;
    this->scene = nullptr;

    delete this->eventHandler;
    this->eventHandler = nullptr;

    delete this->modelHandler;
    this->modelHandler = nullptr;

    delete this->shaderHandler;
    this->shaderHandler = nullptr;

    glfwTerminate();
}

void Engine::init() {
    if (!glfwInit()) {
        fprintf(stderr, "ERROR: could not start GLFW3\n");
        exit(EXIT_FAILURE);
    }
}

void Engine::createScene(int width, int height, const char *title) {
    this->scene = new Scene(width, height, title);
    this->eventHandler = new EventHandler(scene->getWindow()->get());

    // Start GLEW extension handler
    glewExperimental = GL_TRUE;
    glewInit();

    // Initialize OpenGL graphics settings
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);      // Set background color to black and opaque
    glClearDepth(1.0f);                                        // Set background depth to farthest
    glEnable(GL_DEPTH_TEST);                                     // Enable depth testing for z-culling
    glDepthFunc(GL_LEQUAL);                                     // Set the type of depth-test
    glShadeModel(GL_SMOOTH);                                   // Enable smooth shading
    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);  // Nice perspective corrections
}

void Engine::createShaders() {
    this->shaderHandler = new ShaderHandler();
    this->shaderHandler->loadShaderFile("vertexShader", "../assets/shader/vertexShader.frag",GL_VERTEX_SHADER);
    this->shaderHandler->loadShaderFile("fragmentShader", "../assets/shader/fragmentShader.frag",GL_FRAGMENT_SHADER);
}

void Engine::createModels() {
    this->modelHandler = new ModelHandler();
    this->modelHandler->loadModelVar("suziFlat", suziFlat, sizeof(suziFlat), sizeof(suziFlat) / 6 / 4);
    this->modelHandler->loadModelVar("suziSmooth", suziSmooth, sizeof(suziSmooth), sizeof(suziSmooth) / 6 / 4);
    this->modelHandler->loadModelVar("sphere", sphere, sizeof(sphere), sizeof(sphere) / 6 / 4);
    this->modelHandler->loadModelVar("triangle", triangle, sizeof(triangle), sizeof(triangle) / 6 / 4);
    this->modelHandler->loadModelVar("pyramid", pyramid, sizeof(pyramid), sizeof(pyramid) / 6 / 4);
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
    std::cout << "OpenGL Version: " << glGetString(GL_VERSION) << std::endl;
    std::cout << "Using GLEW: " << glewGetString(GLEW_VERSION) << std::endl;
    std::cout << "Vendor: " << glGetString(GL_VENDOR) << std::endl;
    std::cout << "Renderer: " << glGetString(GL_RENDERER) << std::endl;
    std::cout << "GLSL: " << glGetString(GL_SHADING_LANGUAGE_VERSION) << std::endl;
    std::cout << "Using GLFW: " << major << "." << minor << "." << revision << std::endl << std::endl;
}

void Engine::run() {
    lastTick = glfwGetTime();

    while (this->running) {
        this->running = !glfwWindowShouldClose(scene->getWindow()->get());
        double deltaTime = (glfwGetTime() - lastTick) * 1e4;

        glfwPollEvents();
        scene->simulate(deltaTime);
        scene->draw(deltaTime);

        lastTick = glfwGetTime();
    }
}

void Engine::stop() {
    this->running = false;
}

bool Engine::isRunning() const {
    return this->running;
}

Scene* Engine::getScene() {
    return this->scene;
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