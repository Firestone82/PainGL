#include "engine/Engine.h"
#include "listener/event/MouseEvents.h"
#include <iostream>

int main() {
    auto* engine = new Engine();
    engine->init();

    engine->createScene(720, 600, "ZPG");
    engine->createModels();
    engine->createShaders();

    engine->getEventHandler()->addListener(new KeyListener([=](GLFWwindow* window, int key, int scancode, int action, int mods) {
        // Exit engine on ESCAPE key press
        if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
            engine->stop();
        }
    }));

    engine->getEventHandler()->addListener(new WindowSizeListener([=](GLFWwindow* window, int width, int height) {
        // Resize viewport on window resize
        glViewport(0, 0, width, height);

        // Keep aspect ratio
        float ratio = (float) width / (float) height;
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        glOrtho(-ratio, ratio, -1.0f, 1.0f, 1.0f, -1.0f);

        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();

    }));

    auto* leftSuzi = new RenderableEntity(
        engine->getModelHandler()->getModel("suziSmooth"),
        engine->getShaderHandler()->createProgram("fragmentShader", "vertexShader")
    );
    leftSuzi->setPosition(1.0f,0.0f, 0.0f);
    leftSuzi->setScale(0.5f, 0.5f, 0.5f);
    leftSuzi->setRotation(0.0f, -45.0f, 0.0f);
    engine->getScene()->renderEntity(leftSuzi);

    auto* rightSuzi = new RenderableEntity(
            engine->getModelHandler()->getModel("suziSmooth"),
            engine->getShaderHandler()->createProgram("fragmentShader", "vertexShader")
    );
    rightSuzi->setPosition(-1.0f,0.0f, 0.0f);
    rightSuzi->setScale(0.5f, 0.5f, 0.5f);
    rightSuzi->setRotation(0.0f, 45.0f, 0.0f);
    engine->getScene()->renderEntity(rightSuzi);

    auto* pyramid = new RenderableEntity(
            engine->getModelHandler()->getModel("pyramid"),
            engine->getShaderHandler()->createProgram("fragmentShader", "vertexShader")
    );
    pyramid->setPosition(0.0f,-1.0f, 0.0f);
    pyramid->setScale(0.75f, 0.75f, 0.75f);
    pyramid->setRotation(0.0f, 15.0f, 0.0f);
    engine->getScene()->renderEntity(pyramid);

    engine->getEventHandler()->addListener(new KeyListener([=](GLFWwindow* window, int key, int scancode, int action, int mods) {
        // Rotate pyramid on R key press
        if (key == GLFW_KEY_R) {
            pyramid->setRotation(0.0f, pyramid->getRotation().y + 15.0f, 0.0f);
        }
    }));

    auto* sphere = new RenderableEntity(
            engine->getModelHandler()->getModel("sphere"),
            engine->getShaderHandler()->createProgram("fragmentShader", "vertexShader")
    );
    sphere->setPosition(0.0f,1.0f, 0.0f);
    sphere->setScale(0.50f, 0.50f, 0.50f);
    sphere->setRotation(0.0f, 15.0f, 0.0f);
    engine->getScene()->renderEntity(sphere);

    engine->info();
    engine->run();

    fprintf(stdout, "\n[DEBUG] Shutting down engine.\n");
    delete engine;

    exit(EXIT_SUCCESS);
}