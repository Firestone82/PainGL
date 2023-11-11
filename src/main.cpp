#include "Engine.h"
#include <random>

#include "utils/Logger.h"
#include "utils/ColorUtils.h"

#include "scene/light/type/PointLight.h"
#include "scene/light/type/SpotLight.h"
#include "scene/light/type/DirLight.h"
#include "scene/light/type/FlashLight.h"
#include "scene/transformation/curve/BezierCurve.h"

int main() {
	Logger::info("Starting PainGL: Project in ZPG");
	Logger::setDebugMode(true);

	Engine* engine = Engine::getInstance();
	engine->init(1280,720,"PainGL: Project in ZPG");
	engine->info();

	BezierCurve* curve = new BezierCurve({
			                                     {0.0f, 0.0f, 0.0f},
			                                     {2.0f, 4.0f, 0.0f},
			                                     {4.0f, -4.0f, 0.0f},
			                                     {6.0f, 0.0f, 0.0f},
			                                     {4.0f, 4.0f, 0.0f},
			                                     {2.0f, -4.0f, 0.0f},
			                                     {0.0f, 0.0f, 0.0f}
	                                     });

	curve->setResolution(100);

	Scene::Builder sceneBuilder = Scene::createScene("Test Scene");


	sceneBuilder.addLight(
			PointLight::createLight("PointLight")
					.setDiffuse({1.0f, 1.0f, 1.0f})
					.setTransformation(new Transform::Composite({
						new Transform::Translate(0.0f, 5.0f, 0.0f)
					}))
					.build()
	);

	sceneBuilder.addLight(
			PointLight::createLight("PointLight-Far")
					.setDiffuse({1.0f, 1.0f, 1.0f})
					.setTransformation(new Transform::Composite({
						new Transform::Translate(0.0f, 5.0f, 5.0f)
					}))
					.build()
	);

	// Add small ball on each control point
	for (glm::vec3 point : curve->getControlPoints()) {

		sceneBuilder.addEntity(
				Entity::createEntity("Sphere")
						.setModel("sphere")
						.setShaderProgram("modelShader.vert", "blimmLightShader.frag")
						.setTransformation(new Transform::Composite({
							new Transform::Translate(point.x, point.y, point.z),
							new Transform::Scale(0.1f)
						}))
						.build()
		);
	}

	// Draw curve points as small balls
	int i = 0;
	for (glm::vec3 point : curve->getCurvePoints()) {
		if (i++ % 10 != 0) continue;

		sceneBuilder.addEntity(
				Entity::createEntity("Sphere")
						.setModel("sphere")
						.setShaderProgram("modelShader.vert", "blimmLightShader.frag")
						.setTransformation(new Transform::Composite({
							new Transform::Translate(point.x, point.y, point.z),
							new Transform::Scale(0.0000001f)
						}))
						.build()
		);
	}

	sceneBuilder.addEntity(
			Entity::createEntity("Sphere")
					.setModel("sphere")
					.setShaderProgram("modelShader.vert", "blimmLightShader.frag")
					.setSimulateFunction([=](Entity* entity, float deltaTime) {
						static float t = 0.0f;
						static std::vector<glm::vec3> points = curve->getCurvePoints();
						glm::vec3 point = points[(int) (points.size() * t)];

						// Increment t
						t += deltaTime / 2.0f;
						if (t > 1.0f) {
							t = 0.0f;
						}

						// Set position
						entity->getTransformation()->setTransformation(new Transform::Composite({
							new Transform::Translate(point.x, point.y, point.z)
						}));
					})
					.build()
	);

//					.setSky(Sky::createSkyBox("field", Path("../assets/texture/skybox/ocean/")))
//					.setSky(Sky::createSkyDome("field", Path("../assets/texture/skydome/fulldome3.jpg")))
	sceneBuilder.setCameraTarget(glm::vec3 {0.0f, 0.0f, 0.0f});
	sceneBuilder.setCameraPosition(glm::vec3 {0.0f, 3.0f, 8.0f});

	engine->getSceneHandler()->addScene(sceneBuilder.build());

	Logger::info("Starting Engine");
	engine->run();

	delete engine;
	Logger::info("\nExiting PainGL: Project in ZPG");
	exit(EXIT_SUCCESS);
}