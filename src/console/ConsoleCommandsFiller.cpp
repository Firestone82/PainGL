#include "console/ConsoleHandler.h"
#include "Engine.h"
#include "event/type/CameraEvents.h"

#include <glm/vec3.hpp>

void ConsoleHandler::fillCommands() {
	this->addCommand(ConsoleCommand::createCommand("help")
						->setDescription("Displays all available commands")
			            ->setUsage("help")
			            ->setCallback([=](const std::vector<std::string>& args) {
							this->addLog(false,"\n Commands:");

							for (const auto& command : this->getCommands()) {
							   this->addLog(false,"  » %s", command->getUsage().c_str());
							   this->addLog(false,"     # %s", command->getDescription().c_str());
							}
                       })
                       ->build());

	this->addCommand(ConsoleCommand::createCommand("clear")
						->setDescription("Clears the console")
			            ->setUsage("clear")
			            ->setCallback([=](const std::vector<std::string>& args) {
				            this->clearLog();
						})
			            ->build());

	this->addCommand(ConsoleCommand::createCommand("position")
			            ->setDescription("Sets the position of the camera")
			            ->setUsage("position <x> <y> <z>")
			            ->setMinArgs(3)
			            ->setMaxArgs(3)
			            ->setCallback([=](const std::vector<std::string>& args) {
				            float x;
				            float y;
					        float z;

                            try {
	                            x = std::stof(args[1]);
	                            y = std::stof(args[2]);
	                            z = std::stof(args[3]);
                            } catch (std::exception& e) {
	                            this->addLog(false, "[error] %s", e.what());
	                            return;
                            }

							Scene* scene = Engine::getInstance()->getSceneHandler()->getActiveScene();
							if (scene == nullptr) {
								this->addLog(false, "[error] No scene is active");
								return;
							}

                            scene->getCameraHandler()->getCamera()->setPosition(glm::vec3(x, y, z));
                            scene->getCameraHandler()->getCamera()->calculateViewMatrix();
							EventHandler::callEvent(new CameraMoveEvent(scene->getCameraHandler()->getCamera()));

                            this->addLog(false,"\n Camera position set to (%0.2f, %0.2f, %0.2f)", x, y, z);
                        })
                        ->build());

	this->addCommand(ConsoleCommand::createCommand("target")
						->setDescription("Sets the target of the camera")
						->setUsage("target <x> <y> <z>")
						->setMinArgs(3)
						->setMaxArgs(3)
						->setCallback([=](const std::vector<std::string>& args) {
							float x;
							float y;
							float z;

							try {
							   x = std::stof(args[1]);
							   y = std::stof(args[2]);
							   z = std::stof(args[3]);
							} catch (std::exception& e) {
							   this->addLog(false, "[error] %s", e.what());
							   return;
							}

							Scene* scene = Engine::getInstance()->getSceneHandler()->getActiveScene();
							if (scene == nullptr) {
								this->addLog(false, "[error] No scene is active");
								return;
							}

							scene->getCameraHandler()->getCamera()->setTarget(glm::vec3(x, y, z));
							scene->getCameraHandler()->getCamera()->calculateViewMatrix();
							EventHandler::callEvent(new CameraRotateEvent(scene->getCameraHandler()->getCamera()));

					        this->addLog(false, "\n Camera target set to (%0.2f, %0.2f, %0.2f)", x, y, z);
					    })
					   ->build());

	this->addCommand(ConsoleCommand::createCommand("sensitivity")
						->setDescription("Sets the sensitivity of the camera")
						->setUsage("sensitivity <sensitivity>")
						->setMinArgs(0)
						->setMaxArgs(1)
						->setCallback([=](const std::vector<std::string>& args) {
							Scene* scene = Engine::getInstance()->getSceneHandler()->getActiveScene();
							if (scene == nullptr) {
								this->addLog(false, "[error] No scene is active");
								return;
							}

							float sensitivity = scene->getCameraHandler()->getSensitivity();

							if (args.size() == 1) {
								this->addLog(false, "\n Camera sensitivity is %0.2f", sensitivity);
								return;
							}

							try {
								sensitivity = std::stof(args[1]);
								scene->getCameraHandler()->setSensitivity(sensitivity);
							} catch (std::exception& e) {
								this->addLog(false, "[error] %s", e.what());
								return;
							}

							this->addLog(false, "\n Camera sensitivity set to %0.2f", sensitivity);
						})
						->build());

	this->addCommand(ConsoleCommand::createCommand("speed")
						->setDescription("Sets the speed of the camera")
						->setUsage("speed <speed>")
						->setMinArgs(0)
						->setMaxArgs(1)
						->setCallback([=](const std::vector<std::string>& args) {
							Scene* scene = Engine::getInstance()->getSceneHandler()->getActiveScene();
							if (scene == nullptr) {
								this->addLog(false, "[error] No scene is active");
								return;
							}

							float speed = scene->getCameraHandler()->getSpeed();

							if (args.size() == 1) {
								this->addLog(false, "\n Camera speed is %0.2f", speed);
								return;
							}

							try {
								speed = std::stof(args[1]);
								scene->getCameraHandler()->setSpeed(speed);
							} catch (std::exception& e) {
								this->addLog(false, "[error] %s", e.what());
								return;
							}

							this->addLog(false, "\n Camera speed set to %0.2f", speed);
						})
						->build());

	this->addCommand(ConsoleCommand::createCommand("fov")
						->setDescription("Sets the field of view of the camera")
						->setUsage("fov <fov>")
						->setMinArgs(0)
						->setMaxArgs(1)
						->setCallback([=](const std::vector<std::string>& args) {
							Scene* scene = Engine::getInstance()->getSceneHandler()->getActiveScene();
							if (scene == nullptr) {
								this->addLog(false, "[error] No scene is active");
								return;
							}

							float fov = scene->getCameraHandler()->getFov();

							if (args.size() == 1) {
								this->addLog(false, "\n Camera fov is %0.2f", fov);
								return;
							}

							try {
								fov = std::stof(args[1]);
								scene->getCameraHandler()->setFov(fov);
								scene->getCameraHandler()->calculateProjectionMatrix();
							} catch (std::exception& e) {
								this->addLog(false, "[error] %s", e.what());
								return;
							}

							this->addLog(false, "\n Camera fov set to %0.2f", fov);
						})
						->build());

	this->addCommand(ConsoleCommand::createCommand("demo")
						->setDescription("Toggle demo window")
						->setUsage("demo")
						->setCallback([=](const std::vector<std::string>& args) {
							Scene* scene = Engine::getInstance()->getSceneHandler()->getActiveScene();
							if (scene == nullptr) {
								this->addLog(false, "[error] No scene is active");
								return;
							}

							bool state = Engine::getInstance()->getGUIHandler()->isDemoEnabled();

							Engine::getInstance()->getGUIHandler()->setDemoEnabled(!state);
							scene->getCameraHandler()->setMoving(false);

							if (!state) {
								this->setEnabled(false);
								scene->getCameraHandler()->setMoving(false);
							}

							this->addLog(false, "\n Demo window %s", state ? "hidden" : "shown");
						})
						->build());

	this->addCommand(ConsoleCommand::createCommand("vsync")
						->setDescription("Toggle vsync between 20fps, 30fps, 60fps and unlimited")
						->setUsage("vsync <0,1,2,3>")
						->setMinArgs(1)
						->setMaxArgs(1)
						->setCallback([=](const std::vector<std::string>& args) {
							float sync;

							try {
								sync = std::stof(args[1]);
							} catch (std::exception& e) {
								this->addLog(false, "[error] %s", e.what());
								return;
							}

							if (sync < 0 || sync > 3) {
								this->addLog(false, "[error] Vsync must be 0, 1, 2 or 3");
								return;
							}

							glfwSwapInterval(int(sync));
							int fps = int(60 / sync);

							this->addLog(false, "\n Vsync changed to %d (%d fps)", static_cast<int>(sync), (sync == 0 ? 2000 : fps));
						})
						->build());

	this->addCommand(ConsoleCommand::createCommand("gui")
						->setDescription("Toggle GUI from rendering")
						->setUsage("gui")
						->setCallback([=](const std::vector<std::string>& args) {
							bool state = Engine::getInstance()->getGUIHandler()->isEnabled();
							Engine::getInstance()->getGUIHandler()->setEnabled(!state);

							this->addLog(false, "\n GUI %s", state ? "disabled" : "enabled");
						})
						->build());

	this->addCommand(ConsoleCommand::createCommand("quit")
						->setDescription("Quit application")
						->setUsage("quit")
						->setCallback([=](const std::vector<std::string>& args) {
							Engine::getInstance()->stop();
						})
						->build());

	this->addCommand(ConsoleCommand::createCommand("scene")
						->setDescription("Switch to scene")
						->setUsage("scene <scene>")
						->setMinArgs(1)
						->setMaxArgs(1)
						->setCallback([=](const std::vector<std::string>& args) {
							int id;

							try {
								id = std::stoi(args[1]);
							} catch (std::exception& e) {
								this->addLog(false, "[error] %s", e.what());
								return;
							}

							Scene* scene = Engine::getInstance()->getSceneHandler()->getScenes()[id];
							if (scene == nullptr) {
								this->addLog(false, "[error] Scene with id \"%d\" does not exist", id);
								return;
							}

							Engine::getInstance()->getSceneHandler()->setActiveScene(scene);
							this->addLog(false, "\n Scene \"%s\" is now active", scene->getName().c_str());
						})
						->build());

	// TODO: Max FPS command

	// TODO: Static delta time command
}