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

int main() {
	Logger::info("Starting PainGL: Project in ZPG");
	Logger::setDebugMode(true);

	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_real_distribution<> dis(0.0f, 1.0f);

	Engine* engine = Engine::getInstance();
	engine->init(1280,720,"PainGL: Project in ZPG");
	engine->info();

	Scene::Builder sceneBuilder = Scene::createScene("Galaxy Scene");
	sceneBuilder.setSky(Sky::createSkySphere("Galaxy", new Path("../assets/texture/galaxy.png")));
	sceneBuilder.setCameraPosition(glm::vec3 {-25.0f, 15.0f, 25.0f});
	sceneBuilder.setCameraTarget(glm::vec3 {0.0f, 0.0f, 0.0f});

	sceneBuilder.addLight(
			PointLight::createLight("Sun-Light")
					.setAmbient({0.1f, 0.1f, 0.1f})
					.setDiffuse({0.8f, 0.8f, 0.8f})
					.setSpecular({1.0f, 1.0f, 1.0f})
					.setAttenuation({
						2.0f,
						0.00f,
						0.00f
					})
					.build()
	);

	sceneBuilder.addLight(
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
	sceneBuilder.addEntity(sun);

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
	sceneBuilder.addEntity(mercury);

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
	sceneBuilder.addEntity(venus);

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
	sceneBuilder.addEntity(earth);

	Entity* earthMoon = Entity::createEntity("Earth-Moon")
			.setModel("moon")
			.setShaderProgram("modelShader.vert", "blimmLightShader.frag")
			.setTransformation(new Transform::Composite({
                earth->getTransformation()->get(),

                new Transform::Rotation(0.0f, 90.0f, 0.0f, [=](glm::vec3 current) {
	                current.y -= engine->getDeltaTime() * 50.0f;
	                return current;
                }),
				new Transform::Translate(0.0f, 0.0f, 3.0f),
				new Transform::Scale(0.3f)
			}))
			.build();
	sceneBuilder.addEntity(earthMoon);

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
	sceneBuilder.addEntity(mars);

	Entity* marsMoon = Entity::createEntity("Mars-Moon")
			.setModel("moon")
			.setShaderProgram("modelShader.vert", "blimmLightShader.frag")
			.setTransformation(new Transform::Composite({
				mars->getTransformation()->get(),
				new Transform::Scale(1.5f),

				new Transform::Rotation(0.0f, 25.0f, 0.0f, [=](glm::vec3 current) {
					current.y += engine->getDeltaTime() * 25.0f;
					return current;
				}),
				new Transform::Translate(1.5f, 0.0f, 0.0f),
				new Transform::Scale(0.2f)
			}))
			.build();
	sceneBuilder.addEntity(marsMoon);

	Entity* marsMoonSecond = Entity::createEntity("Mars-Moon-Second")
			.setModel("moon")
			.setShaderProgram("modelShader.vert", "blimmLightShader.frag")
			.setTransformation(new Transform::Composite({
		        mars->getTransformation()->get(),
		        new Transform::Scale(1.5f),

		        new Transform::Rotation(0.0f, -25.0f, 0.0f, [=](glm::vec3 current) {
			        current.y += engine->getDeltaTime() * 28.5f;
			        return current;
		        }),
				new Transform::Translate(-1.5f, 0.0f, 0.0f),
				new Transform::Scale(0.2f)
			}))
			.build();
	sceneBuilder.addEntity(marsMoonSecond);

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
	sceneBuilder.addEntity(jupiter);

	Entity* saturn = Entity::createEntity("Saturn")
			.setModel("saturn")
			.setShaderProgram("modelShader.vert", "blimmLightShader.frag")
			.setTransformation(new Transform::Composite({
                new Transform::Rotation(0.0f, 0.0f, 0.0f, [=](glm::vec3 current) {
                    current.y += engine->getDeltaTime() * 12.0f;
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
	sceneBuilder.addEntity(saturn);

	for (int i = 0; i < 6; i++) {
		float radius = dis(gen) * 1.0f + 1.5f;
		float speed = dis(gen) * 38.0f;
		float size = dis(gen) * 0.2f + 0.15f;

		// Random angel from 0 to 360
		float angle = dis(gen) * 360.0f;

		Entity* moon = Entity::createEntity("Saturn-Moon-" + std::to_string(i))
				.setModel("moon")
				.setShaderProgram("modelShader.vert", "blimmLightShader.frag")
				.setTransformation(new Transform::Composite({
					saturn->getTransformation()->get(),

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
		sceneBuilder.addEntity(moon);
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
	sceneBuilder.addEntity(uranus);

	for (int i = 0; i < 5; i++) {
		float radius = dis(gen) * 1.5f + 1.0f;
		float speed = dis(gen) * 32.0f;
		float size = dis(gen) * 0.2f + 0.1f;

		// Random angel from 0 to 360
		float angle = dis(gen) * 360.0f;

		Entity* moon = Entity::createEntity("Uranus-Moon-" + std::to_string(i))
				.setModel("moon")
				.setShaderProgram("modelShader.vert", "blimmLightShader.frag")
				.setTransformation(new Transform::Composite({
					uranus->getTransformation()->get(),
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
		sceneBuilder.addEntity(moon);
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
	sceneBuilder.addEntity(neptune);

	for (int i = 0; i < 10; i++) {
		float radius = dis(gen) * 2.5f + 1.0f;
		float speed = dis(gen) * 25.0f;
		float size = dis(gen) * 0.2f + 0.1f;

		// Random angel from 0 to 360
		float angle = dis(gen) * 360.0f;

		Entity* moon = Entity::createEntity("Neptune-Moon-" + std::to_string(i))
				.setModel("moon")
				.setShaderProgram("modelShader.vert", "blimmLightShader.frag")
				.setTransformation(new Transform::Composite({
					neptune->getTransformation()->get(),
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
		sceneBuilder.addEntity(moon);
	}

	engine->getSceneHandler()->addScene(sceneBuilder.build());

	Scene::Builder curveScene = Scene::createScene("Curve Scene");
	sceneBuilder.setCameraPosition(glm::vec3 {10.0f, 6.0f, 10.0f});
	sceneBuilder.setCameraTarget(glm::vec3 {0.0f, 0.0f, 0.0f});

	curveScene.addLight(
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
				new Transform::Scale(20.0f)
			}))
			.setMaterial(
					Material::createMaterial()
							.addTexture("rockySand", TextureType::DIFFUSE)
							.setTextureScale(20.0f)
							.build()
			)
			.build();
	curveScene.addEntity(ground);

	Entity* tank = Entity::createEntity("Tank")
			.setModel("tank")
			.setShaderProgram("modelShader.vert", "phongLightShader.frag")
			.build();
	curveScene.addEntity(tank);

	// Make that tank shoot a bullet
	Entity* bullet = Entity::createEntity("Bullet")
			.setModel("sphere")
			.setShaderProgram("modelShader.vert", "phongLightShader.frag")
			.setTransformation(new Transform::Composite({
				new Transform::Curve({
					{-2.5f, 1.5f, 0.0f},
					{-5.0f, 1.5f, 0.0f},
					{-10.0f, 0.0f, 0.0f},
				}, 1000.0f, 0.4f),
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
	curveScene.addEntity(bullet);

	engine->getSceneHandler()->addScene(curveScene.build());

	Logger::info("Starting Engine");
	engine->run();

	delete engine;
	Logger::info("\nExiting PainGL: Project in ZPG");
	exit(EXIT_SUCCESS);
}