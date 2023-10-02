#include "engine/Engine.h"
#include <iostream>

int main() {
    Engine* engine = new Engine();
    engine->init();

    engine->createScene(640, 480, "PainGL: Project in ZPG");
    engine->createEventHandler(engine->getScene()->getWindow());
    engine->createModels("../assets/model");
    engine->getModelHandler()->loadModelFile("suziSmoothObj", "../assets/model/object/suzi.obj");
    engine->createShaders("../assets/shader");

    engine->getEventHandler()->addListener(new Listener<KeyPressEvent>([=](KeyPressEvent* event) {
        // Exit engine on ESCAPE key press
        if (event->getKey() == GLFW_KEY_ESCAPE && event->getAction() == GLFW_PRESS) {
            engine->stop();
        }
    }));

    engine->getEventHandler()->addListener(new Listener<WindowCloseEvent>([=](WindowCloseEvent* event) {
        // Exit engine on window close
        engine->stop();
    }));

    engine->getScene()->renderEntity(
            RenderableEntity::createEntity("Suzi Smooth")
                    ->setModel(engine->getModelHandler()->getModel("suziSmooth"))
                    ->setShaderProgram(engine->getShaderHandler()->createProgram("fragmentShader", "vertexShader"))
                    ->setSimulateFunction([=](RenderableEntity* entity, float deltaTime) {
                        auto rotation = entity->getRotation();
                        entity->setRotation(rotation.x, rotation.y + 90.0f * deltaTime, rotation.z);
                    })
                    ->build()
    );

//    engine->getScene()->renderEntity(
//            RenderableEntity::createEntity("Suzi Object")
//                    ->setModel(engine->getModelHandler()->getModel("suziSmoothObj"))
//                    ->setShaderProgram(engine->getShaderHandler()->createProgram("fragmentShader", "vertexShader"))
//                    ->build()
//    );

    engine->info();
    engine->run();

    delete engine;

    exit(EXIT_SUCCESS);
}