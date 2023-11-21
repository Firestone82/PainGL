#include "Engine.h"
#include <random>

#include "utils/Logger.h"
#include "utils/ColorUtils.h"

#include "scene/light/type/PointLight.h"
#include "scene/light/type/SpotLight.h"
#include "scene/light/type/DirLight.h"
#include "scene/light/type/FlashLight.h"
#include "scene/transformation/curve/BezierCurve.h"
#include "scene/transformation/transform/Translate.h"
#include "scene/transformation/transform/Scale.h"
#include "scene/transformation/transform/Curve.h"
#include "scene/transformation/transform/Rotation.h"
#include "event/type/MouseEvents.h"
#include "scene/transformation/curve/BalisticCurve.h"

int main() {
	Logger::info("Starting PainGL: Project in ZPG");
	Logger::setDebugMode(true);

	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_real_distribution<> dis(0.0f, 1.0f);

	Engine* engine = Engine::getInstance();
	engine->init(1280,720,"PainGL: Project in ZPG");
	engine->info();

#if 0 // Galaxy Scene
	Scene::Builder galaxyScene = Scene::createScene("Galaxy Scene");
	galaxyScene.setSky(Sky::createSkySphere("Galaxy", new Path("../assets/texture/skysphere/galaxy.png")));
	galaxyScene.setCameraPosition(glm::vec3 {-25.0f, 15.0f, 25.0f});
	galaxyScene.setCameraTarget(glm::vec3 {0.0f, 0.0f, 0.0f});

	galaxyScene.addLight(
			PointLight::createLight("Sun-Light")
					.setAmbient({0.0f, 0.0f, 0.0f})
					.setDiffuse({1.0f, 1.0f, 1.0f})
					.setSpecular({1.0f, 1.0f, 1.0f})
					.setAttenuation({
						0.5f,
						0.00f,
						0.00f
					})
					.build()
	);

	galaxyScene.addLight(
			DirLight::createLight("Ambient-Sun-Light")
					.setAmbient({0.4f, 0.4f, 0.4f})
					.setDiffuse({0.8f, 0.8f, 0.8f})
					.setSpecular({1.0f, 1.0f, 1.0f})
					.setDirection({0.0f, -1.0f, 0.0f})
					.build()
	);

	Entity* sun = Entity::createEntity("Sun")
			.setModel("sun")
			.setShaderProgram("modelShader.vert", "fullLightShader.frag")
			.setTransformation(new Transform::Composite({
				new Transform::Scale(0.5f)
			}))
			.build();
	galaxyScene.addEntity(sun);

	Entity* mercury = Entity::createEntity("Mercury")
			.setModel("mercury")
			.setShaderProgram("modelShader.vert", "blimmLightShader.frag")
			.setTransformation(new Transform::Composite({
				new Transform::Rotation(0.0f, 15.0f, 0.0f, [=](glm::vec3 current) {
					current.y += engine->getDeltaTime() * 28.0f;
					return current;
				}),
				new Transform::Translate(0.0f, 0.0f, 15.0f),
				new Transform::Scale(0.4f)
			}))
			.build();
	galaxyScene.addEntity(mercury);

	Entity* venus = Entity::createEntity("Venus")
			.setModel("venus")
			.setShaderProgram("modelShader.vert", "blimmLightShader.frag")
			.setTransformation(new Transform::Composite({
                new Transform::Rotation(0.0f, 25.0f, 0.0f, [=](glm::vec3 current) {
                    current.y += engine->getDeltaTime() * 22.5f;
                    return current;
                }),
				new Transform::Translate(0.0f, 0.0f, 18.0f),
				new Transform::Scale(0.9f),
			}))
			.build();
	galaxyScene.addEntity(venus);

	Entity* earth = Entity::createEntity("Earth")
			.setModel("earth")
			.setShaderProgram("modelShader.vert", "blimmLightShader.frag")
			.setTransformation(new Transform::Composite({
                new Transform::Rotation(0.0f, -45.0f, 0.0f, [=](glm::vec3 current) {
                    current.y += engine->getDeltaTime() * 20.0f;
                    return current;
                }),
				new Transform::Translate(0.0f, 0.0f, 21.0f),
			}))
			.build();
	galaxyScene.addEntity(earth);

	Entity* earthMoon = Entity::createEntity("Earth-Moon")
			.setModel("moon")
			.setShaderProgram("modelShader.vert", "blimmLightShader.frag")
			.setTransformation(new Transform::Composite({
                earth->getTransformation()->clone(),

                new Transform::Rotation(0.0f, 90.0f, 0.0f, [=](glm::vec3 current) {
	                current.y -= engine->getDeltaTime() * 50.0f;
	                return current;
                }),
				new Transform::Translate(0.0f, 0.0f, 3.0f),
				new Transform::Scale(0.3f)
			}))
			.build();
	galaxyScene.addEntity(earthMoon);

	Entity* mars = Entity::createEntity("Mars")
			.setModel("mars")
			.setShaderProgram("modelShader.vert", "blimmLightShader.frag")
			.setTransformation(new Transform::Composite({
                new Transform::Rotation(0.0f, -180.0f, 0.0f, [=](glm::vec3 current) {
                    current.y += engine->getDeltaTime() * 22.5f;
                    return current;
                }),
				new Transform::Translate(0.0f, 0.0f, 25.0f),
				new Transform::Scale(0.5f)
			}))
			.build();
	galaxyScene.addEntity(mars);

	Entity* marsMoon = Entity::createEntity("Mars-Moon")
			.setModel("moon")
			.setShaderProgram("modelShader.vert", "blimmLightShader.frag")
			.setTransformation(new Transform::Composite({
				mars->getTransformation()->clone(),
				new Transform::Scale(1.5f),

				new Transform::Rotation(0.0f, 25.0f, 0.0f, [=](glm::vec3 current) {
					current.y += engine->getDeltaTime() * 25.0f;
					return current;
				}),
				new Transform::Translate(1.5f, 0.0f, 0.0f),
				new Transform::Scale(0.2f)
			}))
			.build();
	galaxyScene.addEntity(marsMoon);

	Entity* marsMoonSecond = Entity::createEntity("Mars-Moon-Second")
			.setModel("moon")
			.setShaderProgram("modelShader.vert", "blimmLightShader.frag")
			.setTransformation(new Transform::Composite({
		        mars->getTransformation()->clone(),
		        new Transform::Scale(1.5f),

		        new Transform::Rotation(0.0f, -25.0f, 0.0f, [=](glm::vec3 current) {
			        current.y += engine->getDeltaTime() * 28.5f;
			        return current;
		        }),
				new Transform::Translate(-1.5f, 0.0f, 0.0f),
				new Transform::Scale(0.2f)
			}))
			.build();
	galaxyScene.addEntity(marsMoonSecond);

	Entity* jupiter = Entity::createEntity("Jupiter")
			.setModel("jupiter")
			.setShaderProgram("modelShader.vert", "blimmLightShader.frag")
			.setTransformation(new Transform::Composite({
                new Transform::Rotation(0.0f, 225.0f, 0.0f, [=](glm::vec3 current) {
                    current.y += engine->getDeltaTime() * 35.0f;
                    return current;
                }),
				new Transform::Translate(0.0f, 0.0f, 30.0f),
				new Transform::Scale(2.0f)
			}))
			.build();
	galaxyScene.addEntity(jupiter);

	Entity* saturn = Entity::createEntity("Saturn")
			.setModel("saturn")
			.setShaderProgram("modelShader.vert", "blimmLightShader.frag")
			.setTransformation(new Transform::Composite({
                new Transform::Rotation(0.0f, 0.0f, 0.0f, [=](glm::vec3 current) {
                    current.y += engine->getDeltaTime() * 25.0f;
                    return current;
                }),
				new Transform::Translate(0.0f, 0.0f, 42.0f),
                new Transform::Rotation(-45.0f, 0.0f, 0.0f, [=](glm::vec3 current) {
	                current.z += engine->getDeltaTime() * 15.0f;
	                return current;
                }),
				new Transform::Scale(2.0f)
			}))
			.build();
	galaxyScene.addEntity(saturn);

	for (int i = 0; i < 6; i++) {
		float radius = dis(gen) * 1.0f + 1.5f;
		float speed = dis(gen) * 38.0f;
		float size = dis(gen) * 0.2f + 0.15f;
		float angle = dis(gen) * 360.0f;

		Entity* moon = Entity::createEntity("Saturn-Moon-" + std::to_string(i))
				.setModel("moon")
				.setShaderProgram("modelShader.vert", "blimmLightShader.frag")
				.setTransformation(new Transform::Composite({
					saturn->getTransformation()->clone(),

					new Transform::Rotation(0.0f, angle, 0.0f, [=](glm::vec3 current) {
						current.y += engine->getDeltaTime() * speed;
						return current;
					}),
					new Transform::Translate(radius, 0.0f, 0.0f),
					new Transform::Rotation(0.0f, 0.0f, 0.0f, [=](glm::vec3 current) {
						current.x += engine->getDeltaTime() * speed / 2;
						current.z -= engine->getDeltaTime() * speed / 3;
						return current;
					}),
					new Transform::Translate(0.0f, 0.0f, radius / 2),
					new Transform::Scale(size)
				}))
				.build();
		galaxyScene.addEntity(moon);
	}

	Entity* uranus = Entity::createEntity("Uranus")
			.setModel("uranus")
			.setShaderProgram("modelShader.vert", "blimmLightShader.frag")
			.setTransformation(new Transform::Composite({
				new Transform::Rotation(0.0f, -90.0f, 0.0f, [=](glm::vec3 current) {
					current.y += engine->getDeltaTime() * 20.0f;
					return current;
				}),
				new Transform::Translate(0.0f, 0.0f, 56.0f),
				new Transform::Scale(1.8f)
			}))
			.build();
	galaxyScene.addEntity(uranus);

	for (int i = 0; i < 5; i++) {
		float radius = dis(gen) * 1.5f + 1.0f;
		float speed = dis(gen) * 32.0f;
		float size = dis(gen) * 0.2f + 0.1f;
		float angle = dis(gen) * 360.0f;

		Entity* moon = Entity::createEntity("Uranus-Moon-" + std::to_string(i))
				.setModel("moon")
				.setShaderProgram("modelShader.vert", "blimmLightShader.frag")
				.setTransformation(new Transform::Composite({
					uranus->getTransformation()->clone(),
					new Transform::Rotation(0.0f, angle, 0.0f, [=](glm::vec3 current) {
						current.y += engine->getDeltaTime() * speed;
						return current;
					}),
					new Transform::Translate(radius, 0.0f, 0.0f),
					new Transform::Rotation(0.0f, 0.0f, 0.0f, [=](glm::vec3 current) {
						current.x += engine->getDeltaTime() * speed / 2;
						current.z -= engine->getDeltaTime() * speed / 3;
						return current;
					}),
					new Transform::Translate(0.0f, 0.0f, radius / 2),
					new Transform::Scale(size)
				}))
				.build();
		galaxyScene.addEntity(moon);
	}

	Entity* neptune = Entity::createEntity("Neptune")
			.setModel("neptune")
			.setShaderProgram("modelShader.vert", "blimmLightShader.frag")
			.setTransformation(new Transform::Composite({
				new Transform::Rotation(0.0f, 145.0f, 0.0f, [=](glm::vec3 current) {
					current.y += engine->getDeltaTime() * 15.0f;
					return current;
				}),
				new Transform::Translate(0.0f, 0.0f, 68.0f),
				new Transform::Scale(1.5f)
			}))
			.build();
	galaxyScene.addEntity(neptune);

	for (int i = 0; i < 10; i++) {
		float radius = dis(gen) * 2.5f + 1.0f;
		float speed = dis(gen) * 25.0f;
		float size = dis(gen) * 0.2f + 0.1f;
		float angle = dis(gen) * 360.0f;

		Entity* moon = Entity::createEntity("Neptune-Moon-" + std::to_string(i))
				.setModel("moon")
				.setShaderProgram("modelShader.vert", "blimmLightShader.frag")
				.setTransformation(new Transform::Composite({
					neptune->getTransformation()->clone(),
					new Transform::Scale(1.5f),

					new Transform::Rotation(0.0f, angle, 0.0f, [=](glm::vec3 current) {
						current.y += engine->getDeltaTime() * speed;
						return current;
					}),
					new Transform::Translate(radius, 0.0f, 0.0f),
					new Transform::Rotation(0.0f, 0.0f, 0.0f, [=](glm::vec3 current) {
						current.x += engine->getDeltaTime() * speed / 2;
						current.z -= engine->getDeltaTime() * speed / 3;
						return current;
					}),
					new Transform::Translate(0.0f, 0.0f, radius / 2),
					new Transform::Scale(size)
				}))
				.build();
		galaxyScene.addEntity(moon);
	}

	engine->getSceneHandler()->addScene(galaxyScene.build());
#endif

#if 0 // Tank Scene
	Scene::Builder tankScene = Scene::createScene("Tank Scene");
	tankScene.setCameraPosition(glm::vec3 {10.0f, 6.0f, 10.0f});
	tankScene.setCameraTarget(glm::vec3 {0.0f, 0.0f, 0.0f});

	tankScene.addLight(
			DirLight::createLight("Sun-Light")
					.setAmbient({0.8f, 0.8f, 0.8f})
					.setDiffuse({1.0f, 1.0f, 1.0f})
					.setSpecular({1.0f, 1.0f, 1.0f})
					.build()
	);

	Entity* ground = Entity::createEntity("Ground")
			.setModel("pane")
			.setShaderProgram("modelShader.vert", "phongLightShader.frag")
			.setTransformation(new Transform::Composite({
				new Transform::Scale(50.0f)
			}))
			.setMaterial(
					Material::createMaterial()
							.addTexture("rockySand", TextureType::DIFFUSE)
							.setTextureScale(2.5f)
							.build()
			)
			.build();
	tankScene.addEntity(ground);

	Entity* tank = Entity::createEntity("Tank")
			.setModel("tank")
			.setShaderProgram("modelShader.vert", "phongLightShader.frag")
			.setTransformation(new Transform::Composite({
				new Transform::Translate(0.0f, 0.0f, 0.0f),
            }))
			.build();
	tankScene.addEntity(tank);

	Entity* bullet = Entity::createEntity("Bullet")
			.setModel("sphere")
			.setShaderProgram("modelShader.vert", "phongLightShader.frag")
			.setTransformation(new Transform::Composite({
				new Transform::Translate(0.0f, 0.05f, 0.0f),
				new Transform::Curve({
					{
						{-2.5f, 1.5f, 0.0f},
						{-8.0f, 1.5f, 0.0f},
						{-10.5f, 1.0f, 0.0f},
						{-13.0f, 0.0f, 0.0f}
					},
					{
						{-13.0f, 0.0f, 0.0f},
						{-13.5f, 0.5f, 0.0f},
						{-14.0f, 0.5f, 0.0f},
						{-15.5f, 0.0f, 0.0f}
					},
					{
						{-15.5f, 0.0f, 0.0f},
						{-15.75f, 0.5f, 0.0f},
						{-16.0f, 0.5f, 0.0f},
						{-17.0f, 0.0f, 0.0f}
					},
					{
						{-17.0f, 0.0f, 0.0f},
						{-18.0f, 0.0f, 0.0f},
						{-18.5f, 0.0f, 0.0f},
						{-19.0f, 0.0f, 0.0f}
					}
				}),
				new Transform::Rotation(0.0f, 0.0f, 0.0f, [=](glm::vec3 current) {
					current.z += engine->getDeltaTime() * 200.0f;
					return current;
				}),
				new Transform::Scale(0.1f)
			}))
			.setMaterial(
					Material::createMaterial()
							.addTexture("cannonBullet", TextureType::DIFFUSE)
							.build()
			)
			.build();
	tankScene.addEntity(bullet);

	engine->getSceneHandler()->addScene(tankScene.build());
#endif

#if 1
	Scene::Builder zombieShootingScene = Scene::createScene("Zombie Shooting Scene");
	zombieShootingScene.setCameraPosition(glm::vec3 {10.0f, 6.0f, 10.0f});
	zombieShootingScene.setCameraTarget(glm::vec3 {0.0f, 0.0f, 0.0f});

	zombieShootingScene.addLight(
			DirLight::createLight("Sun-Light")
					.setAmbient({0.8f, 0.8f, 0.8f})
					.setDiffuse({1.0f, 1.0f, 1.0f})
					.setSpecular({1.0f, 1.0f, 1.0f})
					.build()
	);

	Entity* newGround = Entity::createEntity("Ground")
			.setModel("pane")
			.setShaderProgram("modelShader.vert", "phongLightShader.frag")
			.setTransformation(new Transform::Composite({
					new Transform::Scale(50.0f)
			}))
			.setMaterial(
					Material::createMaterial()
							.addTexture("rockySand", TextureType::DIFFUSE)
							.setTextureScale(2.5f)
							.build()
			)
			.build();
	zombieShootingScene.addEntity(newGround);

	Entity* m4 = Entity::createEntity("M4A1")
			.setModel("m4a1s")
			.setShaderProgram("modelShader.vert", "phongLightShader.frag")
			.setSimulateFunction([=](Entity* entity, float delta) {
				Camera* camera = engine->getSceneHandler()->getActiveScene()->getCameraHandler()->getCamera();

				float rotationY = camera->getYaw() + 90.0f;
				float rotationX = camera->getPitch();

				entity->getTransformation()->setTransformation(new Transform::Composite({
						new Transform::Translate(camera->getPosition()),
						new Transform::Rotation(0.0f, -rotationY, 0.0f),
						new Transform::Translate(-0.5f, -0.5f, 0.0f),
						new Transform::Rotation(rotationX, 0.0f, 0.0f),
						new Transform::Scale(0.5f)
					}));
				})
			.build();
	zombieShootingScene.addEntity(m4);

	// Static function to add a zombie
	static auto addZombie = [&](std::string name) {
		float x = dis(gen) * 60.0f - 30.0f;
		float z = dis(gen) * 60.0f - 30.0f;
		float rotation = dis(gen) * 360.0f;
		float scale = dis(gen) * 0.5f + 0.25f;

		Entity* zombie = Entity::createEntity(name)
				.setModel("zombie")
				.setShaderProgram("modelShader.vert", "phongLightShader.frag")
				.setTransformation(new Transform::Composite({
					new Transform::Translate(glm::vec3 {x, 0.0f, z}),
					new Transform::Rotation(0.0f, rotation, 0.0f),
					new Transform::Scale(scale)
				}))
				.build();
		zombieShootingScene.addEntity(zombie);
	};

	for (int i = 0; i < 8; i++) {
		addZombie("Zombie-" + std::to_string(i));
	}

	zombieShootingScene.setSimulateFunction([=](Scene* scene, float delta) {
		if (scene->getName() != "Zombie Shooting Scene") return;

		// Remove zombie on hit by bullet
		for (Entity* entity : scene->getEntityHandler()->getEntities()) {
			if (entity->getModel()->getName() != "zombie") continue;
			BoundingBox boundingBox = entity->getBoundingBox();

			for (Entity* bullet : scene->getEntityHandler()->getEntities()) {
				if (bullet->getName() != "M4A1-Bullet") continue;

				BoundingBox bulletBox = bullet->getBoundingBox();
				if (boundingBox.intersects(bulletBox)) {
					scene->getEntityHandler()->removeEntity(entity);
					scene->getEntityHandler()->removeEntity(bullet);

					// Add new Zombie
					addZombie("Zombie-" + std::to_string(scene->getEntityHandler()->getEntities().size()));

					break;
				}
			}
		}
	});

	Scene* zombieShootingScenePtr = zombieShootingScene.build();

	// Shoot bullet on click
	Engine::getInstance()->getEventHandler()->addListener(new Listener<MouseButtonEvent>([=](MouseButtonEvent* event) {
		if (event->getButton() == GLFW_MOUSE_BUTTON_LEFT && event->getAction() == GLFW_PRESS) {
			Scene* activeScene = engine->getSceneHandler()->getActiveScene();
			Camera* camera = activeScene->getCameraHandler()->getCamera();

			if (activeScene->getName() != zombieShootingScenePtr->getName()) {
				return;
			}

			Transform::Composite* comp = new Transform::Composite({
				m4->getTransformation()->clone(),
				new Transform::Scale(1.5f),
				new Transform::Translate(0.0f, 0.22f, -1.25f),
			});

			comp->calculate();
			glm::vec3 position = comp->resultMatrix()[3];

			Entity* testSphere = Entity::createEntity("M4A1-Bullet")
					.setModel("sphere")
					.setShaderProgram("modelShader.vert", "phongLightShader.frag")
					.setTransformation(new Transform::Composite({
						new Transform::BalisticCurve(position, camera->getTarget(), 22.0f),
						new Transform::Scale(0.04f)
					}))
					.setSimulateFunction([=](Entity* entity, float delta) {
						if (entity->getPosition().y < 0) {
							activeScene->getEntityHandler()->removeEntity(entity);
						}
					})
					.build();
			activeScene->getEntityHandler()->addEntity(testSphere);
		}
	}));

	engine->getSceneHandler()->addScene(zombieShootingScenePtr);
#endif

	Logger::info("Starting Engine");
	engine->run();

	delete engine;
	Logger::info("\nExiting PainGL: Project in ZPG");
	exit(EXIT_SUCCESS);
}