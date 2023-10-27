#include "utils/Logger.h"
#include "Engine.h"
#include <random>

#include "../assets/header/sphere.h"
#include "../assets/header/plain.h"
#include "../assets/header/bushes.h"

int main() {
	Logger::info("Starting PainGL: Project in ZPG");

	Engine* engine = Engine::getInstance();
	engine->init(1280,720,"PainGL: Project in ZPG");
	engine->info();

	engine->getModelHandler()->loadModelVariable("sphere", sphere);
	engine->getModelHandler()->loadModelVariable("plain", plain);
	engine->getModelHandler()->loadModelVariable("bush", bushes);

	engine->getSceneHandler()->addScene(
			#pragma region Scene 0 - Test Scene
			Scene::createScene("Test Scene")
					->addEntity(
							Entity::createEntity("Grid")
									->setModel("grid30m2")
									->setMaterial(
											Material::createMaterial()
													->setObjectColor({0.2f, 0.2f, 0.2f})
													->build()
									)
									->setShaderProgram("modelShader.vert", "lambertLightShader.frag")
									->build()
					)
					->addEntity(
							Entity::createEntity("Tank")
									->setModel("tank")
									->setTransformation(new Transform::Composite({
										new Transform::Translate(0.0f, 1.0f, 0.0f)
									}))
									->setMaterial(
											Material::createMaterial()
													->setTexture(engine->getTextureHandler()->getTexture("tank_diff"))
													->build()
									)
									->setShaderProgram("modelShader.vert", "phongLightShader.frag")
									->build()
					)
					->addLight(
							Light::createLight("Top Light")
									->setTransformation(new Transform::Composite({
										new Transform::Translate(0.0f, 3.0f, 0.0f)
									}))
									->build()
					)
					->build()
			#pragma endregion
			);

	engine->getSceneHandler()->addScene(
			#pragma region Scene 1 - Random Entities
			Scene::createScene("Random Entities")
					->addEntity(
							Entity::createEntity("Pikachu")
									->setModel("pikachu")
									->setMaterial(
											Material::createMaterial()
													->setObjectColor({0.4f, 0.4f, 0.0f})
													->setSpecular(0.2f)
													->setShininess(10.0f)
													->build()
									)
									->setShaderProgram("modelShader.vert", "phongLightShader.frag")
									->build()
					)
					->addEntity(
							Entity::createEntity("Devil")
									->setModel("devil")
									->setMaterial(
											Material::createMaterial()
													->setObjectColor({0.4f, 0.4f, 0.0f})
													->setSpecular(0.2f)
													->setShininess(10.0f)
													->build()
									)
									->setShaderProgram("modelShader.vert", "phongLightShader.frag")
									->setTransformation(new Transform::Composite({
										new Transform::Translate(2.0f, 0.0f, -2.0f),
										new Transform::Rotation(0.0f, -30.0f, 0.0f),
									}))
									->build()
					)
					->addEntity(
							Entity::createEntity("Hollow Knight")
									->setModel("hollowknight")
									->setMaterial(
											Material::createMaterial()
													->setObjectColor({0.4f, 0.0f, 0.4f})
													->setSpecular(0.2f)
													->setShininess(10.0f)
													->build()
									)
									->setShaderProgram("modelShader.vert", "phongLightShader.frag")
									->setTransformation(new Transform::Composite({
										new Transform::Translate(-2.0f, 0.0f, -2.0f),
										new Transform::Rotation(0.0f, 30.0f, 0.0f),
									}))
									->build()
					)
					->addEntity(
							Entity::createEntity("Tank")
									->setModel("tank")
									->setMaterial(
											Material::createMaterial()
													->setObjectColor({0.3f, 0.7f, 0.5f})
													->setSpecular(0.2f)
													->setShininess(10.0f)
													->build()
									)
									->setShaderProgram("modelShader.vert", "phongLightShader.frag")
									->setTransformation(new Transform::Composite({
										new Transform::Translate(2.0f, 0.25f, 3.0f),
										new Transform::Rotation(0.0f, -60.0f, 0.0f),
										new Transform::Scale(0.5f),
									}))
									->build()
					)
					->addEntity(
							Entity::createEntity("Pac-Man")
									->setModel("pacman")
									->setMaterial(
											Material::createMaterial()
													->setObjectColor({0.4f, 0.4f, 0.0f})
													->setSpecular(0.2f)
													->setShininess(16.0f)
													->build()
									)
									->setShaderProgram("modelShader.vert", "phongLightShader.frag")
									->setSimulateFunction([&](Entity* entity, float delta) {
										static float x = -5.0f;
										static float z = -5.0f;
										static float rotation = 0.0f;
										static float speed = 2.0f;

										if (x == -5.0f && z < 5.0f) {
											z += speed * delta;
											rotation = 180.0f;
										} else if (z == 5.0f && x < 5.0f) {
											x += speed * delta;
											rotation = 270.0f;
										} else if (x == 5.0f && z > -5.0f) {
											z -= speed * delta;
											rotation = 0.0f;
										} else if (z == -5.0f && x > -5.0f) {
											x -= speed * delta;
											rotation = 90.0f;
										}

										x = std::clamp(x, -5.0f, 5.0f);
										z = std::clamp(z, -5.0f, 5.0f);
										rotation = std::fmod(rotation, 360.0f);

										entity->getTransformation()->setTransformation(new Transform::Composite({
											new Transform::Translate(x, 0.5f, z),
											new Transform::Rotation(0.0f, rotation, 0.0f),
											new Transform::Scale(0.2f)
										}));
									})
									->build()
							)
					->addEntity(
							Entity::createEntity("Grid")
									->setModel("grid30m2")
									->setMaterial(
											Material::createMaterial()
													->setAmbientColor({0.1f, 0.1f, 0.1f})
													->setObjectColor({0.2f, 0.2f, 0.2f})
													->setSpecular(0.2f)
													->setShininess(10.0f)
													->build()
									)
									->setShaderProgram("modelShader.vert", "staticLightShader.frag")
									->build()
					)
					->addLight(
							Light::createLight("Left Light")
									->setTransformation(new Transform::Composite({
										new Transform::Translate(2.0f, 3.0f, 2.0f)
									}))
									->build()
					)
					->addLight(
							Light::createLight("Right Light")
									->setTransformation(new Transform::Composite({
										new Transform::Translate(-2.0f, 3.0f, 2.0f)
									}))
									->build()
					)
					->addLight(
							Light::createLight("Behind Light")
									->setColor({0.3f, 0.3f, 0.3f})
									->setTransformation(new Transform::Composite({
										new Transform::Translate(0.0f, 3.0f, -2.0f)
									}))
									->build()
					)
					->build()
			#pragma endregion
			);

// 	engine->getSceneHandler()->addScene(
//			#pragma region Scene 2 - Light Test Scene
//			Scene::createScene("Light Test Scene")
//					->addEntity(
//							Entity::createEntity("Sphere - Phong")
//									->setModel("sphere")
//									->setShaderProgram("modelShader.vert", "phongLightShader.frag")
//                                    ->setTransformation(new Transform::Composite({
//                                        new Transform::Translate(0.0f, 2.0f, 0.0f),
//                                    }))
//									->build()
//					)
//					->addEntity(
//							Entity::createEntity("Sphere - Lambert")
//									->setModel("sphere")
//									->setShaderProgram("modelShader.vert", "lambertLightShader.frag")
//                                    ->setTransformation(new Transform::Composite({
//                                        new Transform::Translate(-2.0f, 0.0f, 0.0f),
//                                    }))
//									->build()
//					)
//					->addEntity(
//							Entity::createEntity("Sphere - Blimm")
//									->setModel("sphere")
//									->setShaderProgram("modelShader.vert", "blimmLightShader.frag")
//                                    ->setTransformation(new Transform::Composite({
//                                        new Transform::Translate(0.0f, -2.0f, 0.0f),
//                                    }))
//									->build()
//					)
//					->addEntity(
//							Entity::createEntity("Sphere - Static")
//									->setModel("sphere")
//									->setShaderProgram("modelShader.vert", "staticLightShader.frag")
//                                    ->setTransformation(new Transform::Composite({
//                                        new Transform::Translate(2.0f, 0.0f, 0.0f),
//                                    }))
//									->build()
//					)
//					->addLight(Light::createLight("First")
//							           ->setColor(glm::vec3(1.0f, 1.0f, 1.0f))
//							           ->setTransformation(new Transform::Composite({
//										   new Transform::Translate(0.0f, 0.0f, 0.0f)
//									   }))
//							           ->build())
//                    ->setCameraTarget(glm::vec3 {0.0f, 0.0f, 0.0f})
//                    ->setCameraPosition(glm::vec3 {0.0f, 0.0f, 8.0f})
//					->build()
//			#pragma endregion
//	);

//     float rotations[10] = {0.0f};
//     engine->getSceneHandler()->addScene(
//			#pragma region Scene 3 - Planetary System
//			Scene::createScene("Planetary System")
//					->addEntity(
//							Entity::createEntity("Sun")
//									->setModel("sphere")
//									->setShaderProgram("modelShader.vert", "staticLightShader.frag")
//									->build()
//					)
//					->addEntity(
//							Entity::createEntity("Mercury")
//									->setModel("sphere")
//									->setShaderProgram("modelShader.vert", "lambertLightShader.frag")
//                                    ->setSimulateFunction([&](Entity* entity, float delta) {
//                                        entity->getTransformation()->setTransformation(new Transform::Composite({
//                                            new Transform::Composite({
//                                                new Transform::Rotation(0.0f, rotations[0], 0.0f),
//                                                new Transform::Translate(2.0f, 0.0f, 0.0f),
//                                            }),
//                                            new Transform::Scale(0.2f),
//                                        }));
//
//                                        rotations[0] += 1.0f;
//                                        rotations[0] = fmodf(rotations[0], 360.0f);
//                                    })
//									->build()
//					)
//					->addEntity(
//							Entity::createEntity("Venus")
//									->setModel("sphere")
//									->setShaderProgram("modelShader.vert", "lambertLightShader.frag")
//                                    ->setSimulateFunction([&](Entity* entity, float delta) {
//                                        entity->getTransformation()->setTransformation(new Transform::Composite({
//                                            new Transform::Composite({
//                                                new Transform::Rotation(0.0f, -rotations[1], 0.0f),
//                                                new Transform::Translate(4.0f, 0.0f, 0.0f),
//                                            }),
//                                            new Transform::Scale(0.5f),
//                                        }));
//
//                                        rotations[1] += 0.5f;
//                                        rotations[1] = fmodf(rotations[1], 360.0f);
//                                    })
//									->build()
//                    )
//					->addEntity(
//							Entity::createEntity("Earth")
//									->setModel("sphere")
//									->setShaderProgram("modelShader.vert", "lambertLightShader.frag")
//                                    ->setSimulateFunction([&](Entity* entity, float delta) {
//                                        entity->getTransformation()->setTransformation(new Transform::Composite({
//                                            new Transform::Composite({
//                                                new Transform::Rotation(0.0f, rotations[2], 0.0f),
//                                                new Transform::Translate(6.0f, 0.0f, 0.0f),
//                                            }),
//                                            new Transform::Scale(0.5f),
//                                        }));
//
//                                        rotations[2] += 0.6f;
//                                        rotations[2] = fmodf(rotations[2], 360.0f);
//                                    })
//									->build()
//					)
//					->addEntity(
//							Entity::createEntity("Earth-Moon")
//									->setModel("sphere")
//									->setShaderProgram("modelShader.vert", "lambertLightShader.frag")
//                                    ->setSimulateFunction([&](Entity* entity, float delta) {
//                                        entity->getTransformation()->setTransformation(new Transform::Composite({
//                                            new Transform::Composite({
//                                                new Transform::Rotation(0.0f, rotations[2], 0.0f),
//                                                new Transform::Translate(6.0f, 0.0f, 0.0f),
//                                            }),
//                                            new Transform::Composite({
//                                                new Transform::Rotation(0.0f, rotations[3], 0.0f),
//                                                new Transform::Translate(1.0f, 0.0f, 0.0f),
//                                            }),
//                                            new Transform::Scale(0.15f),
//                                        }));
//
//                                        rotations[3] += 0.4f;
//                                        rotations[3] = fmodf(rotations[3], 360.0f);
//                                    })
//									->build()
//                    )
//					->addEntity(
//							Entity::createEntity("Mars")
//									->setModel("sphere")
//									->setShaderProgram("modelShader.vert", "lambertLightShader.frag")
//                                    ->setSimulateFunction([&](Entity* entity, float delta) {
//                                        entity->getTransformation()->setTransformation(new Transform::Composite({
//                                            new Transform::Composite({
//                                                new Transform::Rotation(0.0f, rotations[4], 0.0f),
//                                                new Transform::Translate(9.0f, 0.0f, 0.0f),
//                                            }),
//                                            new Transform::Scale(0.25f),
//                                        }));
//
//                                        rotations[4] += 0.35f;
//                                        rotations[4] = fmodf(rotations[4], 360.0f);
//                                    })
//									->build()
//					)
//					->addEntity(
//							Entity::createEntity("Mars-Moon-1")
//									->setModel("sphere")
//									->setShaderProgram("modelShader.vert", "lambertLightShader.frag")
//                                    ->setSimulateFunction([&](Entity* entity, float delta) {
//                                        entity->getTransformation()->setTransformation(new Transform::Composite({
//                                            new Transform::Composite({
//                                                new Transform::Rotation(0.0f, rotations[4], 0.0f),
//                                                new Transform::Translate(9.0f, 0.0f, 0.0f),
//                                            }),
//                                            new Transform::Composite({
//                                                new Transform::Rotation(0.0f, rotations[5], 0.0f),
//                                                new Transform::Translate(0.5f, 0.0f, 0.0f),
//                                            }),
//                                            new Transform::Scale(0.1f),
//                                        }));
//
//                                        rotations[5] += 0.4f;
//                                        rotations[5] = fmodf(rotations[5], 360.0f);
//                                    })
//									->build()
//					)
//					->addEntity(
//							Entity::createEntity("Mars-Moon-2")
//									->setModel("sphere")
//									->setShaderProgram("modelShader.vert", "lambertLightShader.frag")
//                                    ->setSimulateFunction([&](Entity* entity, float delta) {
//                                        entity->getTransformation()->setTransformation(new Transform::Composite({
//                                            new Transform::Composite({
//                                                new Transform::Rotation(0.0f, rotations[4], 0.0f),
//                                                new Transform::Translate(9.0f, 0.0f, 0.0f),
//                                            }),
//                                            new Transform::Composite({
//                                                new Transform::Rotation(rotations[6] * 0.5, rotations[6], 0.0f),
//                                                new Transform::Translate(1.0f, 0.0f, 0.0f),
//                                            }),
//                                            new Transform::Scale(0.05f),
//                                        }));
//
//                                        rotations[6] += 1.0f;
//                                        rotations[6] = fmodf(rotations[6], 360.0f);
//                                    })
//									->build()
//					)
//                    ->addEntity(
//                            Entity::createEntity("Jupiter")
//                                    ->setModel("sphere")
//                                    ->setShaderProgram("modelShader.vert", "lambertLightShader.frag")
//                                    ->setSimulateFunction([&](Entity* entity, float delta) {
//                                        entity->getTransformation()->setTransformation(new Transform::Composite({
//                                            new Transform::Composite({
//                                                new Transform::Rotation(0.0f, rotations[7], 0.0f),
//                                                new Transform::Translate(12.0f, 0.0f, 0.0f),
//                                            }),
//                                            new Transform::Scale(1.2f),
//                                        }));
//
//                                        rotations[7] += 0.85f;
//                                        rotations[7] = fmodf(rotations[7], 360.0f);
//                                    })
//                                    ->build()
//                    )
//					->addLight(Light::createLight("First")
//							           ->setColor(glm::vec3(1.0f, 1.0f, 0.0f))
//							           ->build())
//                    ->setCameraTarget(glm::vec3 {0.0f, 0.0f, 0.0f})
//                    ->setCameraPosition(glm::vec3 {6.0f, 15.0f, 6.0f})
//					->build()
//			#pragma endregion
//	);

//	Scene::Builder* forestSceneBuilder = Scene::createScene("Forest Scene");
//
//	std::mt19937 gen(std::random_device{}());
//	std::uniform_real_distribution<> randomPosition(-15.0f, 15.0f);
//	std::uniform_real_distribution<> randomRotation(0.0f, 360.0f);
//	std::uniform_real_distribution<> randomColor(0.0f, 255.0f);
//	std::uniform_int_distribution<> randomModel(0, 4);
//
//	for (int i = 0; i < 100; i++) {
//		static std::string models[5] = {"tree", "bush", "suzi", "devil", "hollowknight"};
//		std::string model = models[randomModel(gen)];
//
//		// Random color
//
//		forestSceneBuilder->addEntity(
//			Entity::createEntity(model + std::to_string(i))
//					->setModel(model)
//					->setObjectColor({
//						randomColor(gen) / 255.0f,
//						randomColor(gen) / 255.0f,
//						randomColor(gen) / 255.0f,
//						})
//					->setSpecular(0.2f)
//					->setShininess(10.0f)
//					->setShaderProgram("modelShader.vert", "phongLightShader.frag")
//					->setTransformation(new Transform::Composite({
//						new Transform::Translate(randomPosition(gen), 0.0f, randomPosition(gen)),
//						new Transform::Rotation(0.0f, randomRotation(gen), 0.0f),
//						new Transform::Scale(model == "tree" ? 5.0f : model == "bush" ? 3.0f : 1.0f),
//					}))
//					->build()
//		);
//	}
//
//	forestSceneBuilder->addLight(
//			Light::createLight("Top Light")
//					->setTransformation(new Transform::Composite({
//						new Transform::Translate(0.0f, 3.0f, 0.0f)
//					}))
//					->build()
//	);
//
//	engine->getSceneHandler()->addScene(forestSceneBuilder->build());

	engine->run();

	delete engine;
	Logger::info("\nExiting PainGL: Project in ZPG");
	exit(EXIT_SUCCESS);
}