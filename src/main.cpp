#include "engine/Engine.h"
#include <iostream>

int main() {
    Engine* engine = new Engine();
    engine->init();

    engine->createScene(640, 480, "PainGL: Project in ZPG");
    engine->createEventHandler(engine->getScene()->getWindow());
    engine->createModels();
    engine->getModelHandler()->loadModelFile("suziSmoothObj", "../assets/model/suzi.obj");
    engine->createShaders();

    engine->getEventHandler()->addListener(new KeyListener([=](GLFWwindow *window, int key, int scancode, int action, int mods) {
        // Exit engine on ESCAPE key press
        if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
            engine->stop();
        }
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

    fprintf(stdout, "\n[DEBUG] Shutting down engine.\n");
    delete engine;

    exit(EXIT_SUCCESS);
}