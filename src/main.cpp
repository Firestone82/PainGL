#include "Engine.h"
#include "Logger.h"
#include <iostream>

int main() {
    Logger::info("Starting PainGL: Project in ZPG");

    Engine* engine = new Engine();
    engine->init();

    engine->createEventHandler();
    engine->createScene(1280, 920, "Oh, PainGL: Project in ZPG");
    engine->createGUI(engine->getScene()->getWindowHandler());
    engine->createModels("../assets/model/object");
    engine->createShaders("../assets/shader");
	engine->createConsole();

    static float y = 0.0f;
    static float x = 0.0f;

    engine->getScene()->renderEntity(
            RenderableEntity::createEntity("Gift")
                     ->setModel(engine->getModelHandler()->getModel("gift"))
                     ->setShaderProgram(engine->getShaderHandler()->createProgram("fragmentShader", "vertexShader"))
                     ->setSimulateFunction([=](RenderableEntity* entity, float deltaTime) {
                         entity->getTransformation()->setTransformation(new Transform::Composite({
							 new Transform::Composite({
								 new Transform::Rotation(0.0f, x, 0.0f),
								 new Transform::Translate(0.0f, 1.0f, 2.0f),
							 }),
							 new Transform::Scale(1.5f),
							 new Transform::Rotation(0.0f, x, 0.0f),
                         }));
                         x += 1;
                     })
                     ->build());

    engine->getScene()->renderEntity(
            RenderableEntity::createEntity("Suzi")
                     ->setModel(engine->getModelHandler()->getModel("suzi"))
                     ->setShaderProgram(engine->getShaderHandler()->createProgram("fragmentShader", "vertexShader"))
                     ->setSimulateFunction([=](RenderableEntity* entity, float deltaTime) {
                         entity->getTransformation()->setTransformation(new Transform::Composite({
							 new Transform::Composite({
								 new Transform::Rotation(0.0f, x, 0.0f),
								 new Transform::Translate(0.0f, 1.0f, 2.0f),
							 }),
							 new Transform::Composite({
								 new Transform::Rotation(0.0f, y, 0.0f),
								 new Transform::Translate(0.0f, 0.0f, 2.0f),
							}),
							new Transform::Scale(0.5f),
							new Transform::Rotation(0.0f, y, 0.0f),
                         }));
                         y += 1;
                     })
                     ->build());

    engine->getScene()->renderEntity(
            RenderableEntity::createEntity("grid20m20x20")
                    ->setModel(engine->getModelHandler()->getModel("grid20m20x20"))
                    ->setShaderProgram(engine->getShaderHandler()->createProgram("fragmentShader", "grayVertexShader"))
                    ->build()
    );

    engine->getScene()->renderEntity(
            RenderableEntity::createEntity("stred")
                    ->setModel(engine->getModelHandler()->getModel("sphere"))
                    ->setShaderProgram(engine->getShaderHandler()->createProgram("fragmentShader", "grayVertexShader"))
                    ->setTransformation(new Transform::Composite({
                        new Transform::Scale(0.1f),
                    }))
                    ->build()
    );

    engine->info();
    engine->run();

    delete engine;
    exit(EXIT_SUCCESS);
}