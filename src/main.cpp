#include "engine/Engine.h"
#include "logger/Logger.h"
#include <iostream>

int main() {
    Logger::info("Starting PainGL: Project in ZPG");

    Engine* engine = new Engine();
    engine->init();

    engine->createScene(1280, 720, "PainGL: Project in ZPG");
    engine->createEventHandler(engine->getScene()->getWindow());
    engine->createGUI(engine->getScene()->getWindow());
    engine->createModels("../assets/model/object");
    engine->createShaders("../assets/shader");

    // Exit engine on ESCAPE key press
    engine->getEventHandler()->addListener(new Listener<KeyPressEvent>([=](KeyPressEvent* event) {
        if (event->getKey() == GLFW_KEY_ESCAPE && event->getAction() == GLFW_PRESS) {
            engine->stop();
        }
    }));

    // Exit engine on window close
    engine->getEventHandler()->addListener(new Listener<WindowCloseEvent>([=](WindowCloseEvent* event) {
        engine->stop();
    }));

    engine->getScene()->renderEntity(
            RenderableEntity::createEntity("Backpack")
                    ->setModel(engine->getModelHandler()->getModel("backpack"))
                    ->setShaderProgram(engine->getShaderHandler()->createProgram("fragmentShader", "vertexShader"))
                    ->setSimulateFunction([=](RenderableEntity* entity, float deltaTime) {
                        auto rotation = entity->getRotation();
                        entity->setRotation(rotation.x, rotation.y + (45.0f * deltaTime), rotation.z);
                    })
                    ->setScale(0.25f)
                    ->build()
    );

    engine->getScene()->renderEntity(
            RenderableEntity::createEntity("M4")
                    ->setModel(engine->getModelHandler()->getModel("m4"))
                    ->setShaderProgram(engine->getShaderHandler()->createProgram("fragmentShader", "vertexShader"))
                    ->setSimulateFunction([=](RenderableEntity* entity, float deltaTime) {
                        auto rotation = entity->getRotation();
                        entity->setRotation(rotation.x, rotation.y + (45.0f * deltaTime), rotation.z);
                    })
                    ->setPosition(-2.0f, 0.0f, 0.0f)
                    ->setScale(0.25f)
                    ->build()
    );

    engine->getScene()->renderEntity(
            RenderableEntity::createEntity("Suzi")
                    ->setModel(engine->getModelHandler()->getModel("suzi"))
                    ->setShaderProgram(engine->getShaderHandler()->createProgram("fragmentShader", "vertexShader"))
                    ->setSimulateFunction([=](RenderableEntity* entity, float deltaTime) {
                        auto rotation = entity->getRotation();
                        entity->setRotation(rotation.x, rotation.y + (45.0f * deltaTime), rotation.z);
                    })
                    ->setPosition(2.0f, 0.0f, 0.0f)
                    ->setScale(0.50f)
                    ->build()
    );

    engine->info();
    engine->run();

    delete engine;
    exit(EXIT_SUCCESS);
}