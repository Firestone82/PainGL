#include "Engine.h"
#include <random>

#include "utils/Logger.h"
#include "utils/ColorUtils.h"

#include "scene/light/type/PointLight.h"
#include "scene/light/type/SpotLight.h"
#include "scene/light/type/DirLight.h"
#include "scene/light/type/FlashLight.h"

#include "../assets/model/header/sphere.h"
#include "../assets/model/header/plain.h"

int main() {
	Logger::info("Starting PainGL: Project in ZPG");

	Engine* engine = Engine::getInstance();
	engine->init(1280,720,"PainGL: Project in ZPG");
	engine->info();

	engine->getModelHandler()->loadModelVariable("sphere", sphere);
	engine->getModelHandler()->loadModelVariable("plain", plain);

	engine->getSceneHandler()->addScene(
			Scene::createScene("Light Test Scene")
					.addEntity(
							Entity::createEntity("Hollow Knight")
									.setModel("hollowknight")
									.setShaderProgram("modelShader.vert", "blimmLightShader.frag")
									.build()
					)
//					.addEntity(
//							Entity::createEntity("Backpack")
//									.setModel("backpack")
//									.setShaderProgram("modelShader.vert", "blimmLightShader.frag")
//									.setTransformation(new Transform::Composite({
//										new Transform::Translate(0.0f, 0.0f, 8.0f),
//									}))
//									.build()
//					)
//					.addEntity(
//							Entity::createEntity("plain")
//									.setModel("plainModel")
//									.setShaderProgram("modelShader.vert", "phongLightShader.frag")
//									.setTransformation(new Transform::Composite({
//										new Transform::Scale(50.0f)
//									}))
//									.build()
//					)
//					.addEntity(
//							Entity::createEntity("Plain")
//									.setModel("plain")
//									.setShaderProgram("modelShader.vert", "lambertLightShader.frag")
//									.setTransformation(new Transform::Composite({
//										new Transform::Scale(50.0f)
//									}))
//									.build()
//					)
//					.addEntity(
//							Entity::createEntity("SkyDome")
//									.setModel("skydome")
//									.setShaderProgram("modelShader.vert", "lambertLightShader.frag")
//									.setTransformation(new Transform::Composite({
//                                        new Transform::Translate(0.0f, 10.0f, 0.0f),
////										new Transform::Scale(50.0f)
//									}))
//									.build()
//					)
//					.addEntity(
//							Entity::createEntity("Backpack")
//									.setModel("backpack")
//									.setShaderProgram("modelShader.vert", "blimmLightShader.frag")
//									.setSimulateFunction([&](Entity* entity, float delta) {
//										static float rotation = 0.0f;
//
//										rotation += 30.0f * delta;
//										rotation = std::fmod(rotation, 360.0f);
//
//										entity->getTransformation()->setTransformation(new Transform::Composite({
//											new Transform::Translate(0.0f, 1.0f, 0.0f),
//											new Transform::Rotation(0.0f, rotation, 0.0f),
//											new Transform::Scale(0.5f)
//										}));
//									})
//									.build()
//					)
//					.addLight(
//							SpotLight::createLight("SpotLight-Red")
//									.setColor(glm::vec3(1.0f, 0.0f, 0.0f))
//									.setDirection(glm::vec3(0.0f, -1.0f, 0.0f))
//									.setTransformation(new Transform::Composite({
//										new Transform::Translate(0.0f, 8.0f, 1.0f)
//									}))
//									.build()
//					)
//					.addLight(
//							SpotLight::createLight("SpotLight-Green")
//									.setColor(glm::vec3(0.0f, 1.0f, 0.0f))
//									.setDirection(glm::vec3(0.0f, -1.0f, 0.0f))
//									.setTransformation(new Transform::Composite({
//										new Transform::Translate(0.0f, 8.0f, -1.0f)
//									}))
//									.build()
//					)
//					.addLight(
//							SpotLight::createLight("SpotLight-Blue")
//									.setColor(glm::vec3(0.0f, 0.0f, 1.0f))
//									.setDirection(glm::vec3(0.0f, -1.0f, 0.0f))
//									.setTransformation(new Transform::Composite({
//										new Transform::Translate(1.0f, 8.0f, 0.0f)
//									}))
//									.build()
//					)
					.addLight(
							DirLight::createLight("DirLight")
									.setColor(glm::vec3(1.0f, 1.0f, 1.0f))
									.setDirection({0.0f, -1.0f, 0.0f})
									.build()
					)
					.addLight(
							DirLight::createLight("DirLight")
									.setColor(glm::vec3(1.0f, 1.0f, 1.0f))
									.setDirection({0.0f, 0.0f, -1.0f})
									.build()
					)
					.addLight(
							SpotLight::createLight("SpotLight")
									.setColor(glm::vec3(1.0f, 1.0f, 1.0f))
									.setDirection({0.0f, -1.0f, 0.0f})
									.setTransformation(new Transform::Composite({
										new Transform::Translate(0.0f, 5.0f, 0.0f)
									}))
									.build()
					)
//					.setSkyBox("field", {
//						Path("../assets/texture/skybox/ocean/right.jpg"),
//						Path("../assets/texture/skybox/ocean/left.jpg"),
//						Path("../assets/texture/skybox/ocean/top.jpg"),
//						Path("../assets/texture/skybox/ocean/bottom.jpg"),
//						Path("../assets/texture/skybox/ocean/front.jpg"),
//						Path("../assets/texture/skybox/ocean/back.jpg")
//					})
					.setCameraTarget(glm::vec3 {0.0f, 0.0f, 0.0f})
					.setCameraPosition(glm::vec3 {0.0f, 3.0f, 8.0f})
					.build()
	);

//	Scene::Builder forestSceneBuilder = Scene::createScene("Forest Scene");
//
//	std::mt19937 gen(std::random_device{}());
//	std::uniform_real_distribution<> randomPosition(-25.0f, 25.0f);
//	std::uniform_real_distribution<> randomRotation(0.0f, 360.0f);
//	std::uniform_real_distribution<> randomColor(0.0f, 255.0f);
//	std::uniform_int_distribution<> randomModel(0, 4);
//
//	for (int i = 0; i < 50; i++) {
//		static std::string models[5] = {"tree", "rat", "tank", "devil", "hollowknight"};
//		std::string model = models[randomModel(gen)];
//
//		forestSceneBuilder.addEntity(
//				Entity::createEntity(model + std::to_string(i))
//						.setModel(model)
//						.setShaderProgram("modelShader.vert", "phongLightShader.frag")
//						.setMaterial(
//								Material::createMaterial()
//									.setDiffuseColor({
//										randomColor(gen) / 255.0f,
//										randomColor(gen) / 255.0f,
//										randomColor(gen) / 255.0f
//									})
//									.build()
//						)
//						.setTransformation(new Transform::Composite({
//							new Transform::Translate(randomPosition(gen), model == "tank" ? 1.0f : 0.0f, randomPosition(gen)),
//							new Transform::Rotation(0.0f, randomRotation(gen), 0.0f),
//							new Transform::Scale(model == "tree" ? 5.0f : model == "rat" ? 3.0f : 1.0f),
//						}))
//						.build()
//		);
//	}
//
//	forestSceneBuilder.addEntity(
//			Entity::createEntity("Ground")
//					.setModel("plain")
//					.setMaterial(
//							Material::createMaterial()
//								.setDiffuseColor({
//									0.0f,
//									0.5f,
//									0.0f
//								})
//								.build()
//					)
//					.setShaderProgram("modelShader.vert", "lambertLightShader.frag")
//					.setTransformation(new Transform::Composite({
//						new Transform::Scale(100.0f),
//					}))
//					.build()
//	);
//
//	forestSceneBuilder.addLight(
//			DirLight::createLight("Top Light")
//					.setAmbient(glm::vec3(0.1f, 0.1f, 0.1f))
//					.setDiffuse(glm::vec3(0.0f, 0.0f, 0.0f))
//					.setSpecular(glm::vec3(0.0f, 0.0f, 0.0f))
//					.setDirection(glm::vec3(0.0f, -1.0f, 0.0f))
//					.build()
//	);
//
//	forestSceneBuilder.addLight(
//			PointLight::createLight("Point Light")
//					.setColor(glm::vec3(1.0f, 1.0f, 1.0f))
//					.setTransformation(new Transform::Composite({
//						new Transform::Translate(0.0f, 5.0f, 0.0f)
//					}))
//					.build()
//	);
//
//	forestSceneBuilder.addLight(
//			FlashLight::createLight("FlashLight")
//					.setColor(glm::vec3(1.0f, 1.0f, 1.0f))
//					.setAttenuation({
//						1.0,
//						0.05,
//						0.001
//					})
//					.build()
//	);
//
//	engine->getSceneHandler()->addScene(forestSceneBuilder.build());

	Logger::info("Starting Engine");
	engine->run();

	delete engine;
	Logger::info("\nExiting PainGL: Project in ZPG");
	exit(EXIT_SUCCESS);
}